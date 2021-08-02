#ifndef ImageDrawer_h
#define ImageDrawer_h
#include "ImageDrawer.h"
#endif

/*
TODO: 
- get basic drawing set up
- get movement working 
- implement bullet and enemy spawning
- implement level changes and main mechanic
- get text done
- draw enemies and player
- create title screen
- draw backgrounds
*/

upng_error err;
struct cached_img blank_img{nullptr, 0, 0, 0, GL_NONE, GL_NONE};

// stores all of the loaded images to prevent memory leaks
struct cached_img **loaded_imgs = new struct cached_img*[64];
int stacksize = 0;

struct cached_img create_empty_image(){
    return cached_img{nullptr,0,0,0,GL_NONE,GL_NONE};
}

struct cached_img create_empty_image(int height, int width){}
struct cached_img create_empty_image(int height, int width, GLenum format, GLenum type){}

struct cached_img *cache_image(struct cached_img *x, unsigned int height, unsigned int width, unsigned int pixel_depth, GLenum format, GLenum type, GLvoid *pixels){
    int imgsize = width*height*pixel_depth;
    x->indx = (unsigned char*)std::malloc(imgsize);
    unsigned char* a = (unsigned char*)pixels;
    for (int i=0;i<imgsize;i++) {
        x->indx[i] = a[i];
    }
    x->format = format;
    x->type = type;
    x->height = height;
    x->width = width;
    loaded_imgs[stacksize] = x; // makes sure stack stays in order
    stacksize++;
    return x;
}

upng_error get_png_error() {
    return err;
}

void add_gl_props(struct cached_img *c, upng_format frmt) {
    if (frmt == UPNG_RGB8) {
        c->format = GL_RGB;
        c->type = GL_UNSIGNED_BYTE;
    } else if (frmt == UPNG_RGB16) {
        c->format = GL_RGB;
        c->type = GL_UNSIGNED_SHORT;
    } else if (frmt == UPNG_RGBA8) {
        c->format = GL_RGBA;
        c->type = GL_UNSIGNED_BYTE;
    } else if (frmt == UPNG_RGBA16) {
        c->format = GL_RGBA;
        c->type = GL_UNSIGNED_SHORT;
    } else if (frmt == UPNG_LUMINANCE8) {
        c->format = GL_LUMINANCE;
        c->type = GL_UNSIGNED_BYTE;
    } else if (frmt == UPNG_LUMINANCE_ALPHA8) {
        c->format = GL_LUMINANCE_ALPHA;
        c->type = GL_UNSIGNED_BYTE;
    }
}

struct cached_img *loadPngImg(struct cached_img *x, const char *pth) {
    upng_t* upng;
    upng = upng_new_from_file(pth);
    if (upng != NULL) {
        upng_decode(upng);
        err = upng_get_error(upng);
        if (err == UPNG_EOK) {
            x->indx = (unsigned char*)std::malloc(upng_get_size(upng));
            for (int i=0;i<upng_get_size(upng);i++) {
                x->indx[i] = upng_get_buffer(upng)[i];
            }
            upng_format frmt = upng_get_format(upng);
            add_gl_props(x, frmt);
            x->height = upng_get_height(upng);
            x->width = upng_get_width(upng);
            x->pixelsize = upng_get_pixelsize(upng);
        }
        upng_free(upng);
    }
    loaded_imgs[stacksize] = x; // makes sure stack stays in order
    stacksize++;
    return x;
}

// UNLOADING

void closeAllImgs() {
    for (;stacksize>0;stacksize--) {
        std::free(loaded_imgs[stacksize-1]->indx);
        std::free(loaded_imgs[stacksize-1]);
    }
}

// DRAWING

int getFormatDepth(GLenum format, GLenum type) {
    int multiplier = 1, base = 3;
    switch (type) {
        case GL_UNSIGNED_BYTE:
        case GL_BYTE:
            multiplier = 1;
            break;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            multiplier = 2;
            break;
        case GL_INT:
        case GL_UNSIGNED_INT:
            multiplier = 3;
            break;
    };
    switch (format) {
        case GL_RGB:
            base = 3;
            break;
        case GL_RGBA:
            base = 4;
            break;
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_LUMINANCE:
        case GL_STENCIL:
            base = 1;
            break;
        case GL_LUMINANCE_ALPHA:
            base = 2;
            break;
    };
    return multiplier * base;
}

unsigned char *flip_image(unsigned char *orig, unsigned int h, unsigned int w, unsigned int d) {
    d=4;
    unsigned char *end = orig+(h*w*d);
    unsigned char *complement = end-(w*d);
    int i;
    int size = w*h*d;
    unsigned char temp; // because I can't be bothered
    
    for (int y=0;y<h;y++) {
        for (int x=0;x<w*d;x++) {
             i = y*w*d+x;
            // complement = end-((y+1)*w*d)+x;
            // complement = ;
            // *complement ^= orig[i];
            // orig[i] ^= *complement;
            // *complement ^= orig[i];

            // temp = orig[size-i];
            // orig[size-i] = orig[i];
            // orig[i] = temp;

            orig[i] = 1;
        }
    }
    
   /*
    for (i=0;i<size;i++) {
        temp = orig[i];
        orig[i] = 'u';
        orig[i] = orig[size-w*4];
        // orig[size-i-1] = temp;
    }
    */
    return orig;
}

unsigned char *flip_image(struct cached_img target) {
    return flip_image(target.indx, target.height, target.width, target.pixelsize);
}

void draw_cached_img (struct cached_img img) {
    glDrawPixels(
        img.width,
        img.height,
        img.format,
        img.type,
        img.indx
    );
}

bool safe_draw_cached_img (struct cached_img img, float x, float y, float sx, float sy) {
    float *p_raster_pos;
    float *p_zoom_x;
    float *p_zoom_y;
    unsigned char *position_valid;
    glGetFloatv(GL_CURRENT_RASTER_POSITION, p_raster_pos);
    glGetFloatv(GL_ZOOM_X, p_zoom_x);
    glGetFloatv(GL_ZOOM_Y, p_zoom_y);
    glRasterPos2f(x, y);
    glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, position_valid);
    if (!(*position_valid)) {
        glRasterPos4f(p_raster_pos[0], p_raster_pos[1], p_raster_pos[2], p_raster_pos[3]);
        return false;
    }
    glPixelZoom(sx, sy);
    draw_cached_img(img);
    glRasterPos4f(p_raster_pos[0], p_raster_pos[1], p_raster_pos[2], p_raster_pos[3]);
    glPixelZoom(*p_zoom_x, *p_zoom_y);
    return true;
}

void output(float x, float y, float r, float g, float b, void* font, const char *string) {
   glColor3f( r, g, b );
   glRasterPos2f(x, y);
   // glutBitmapString(string);
   int len, i;
   len = (int)strlen(string);
   for (i = 0; i < len; i++) {
      glutBitmapCharacter(font, string[i]);
   }
}

bool center_cached_img (struct cached_img img, float x, float y, float sx, float sy, float window_width, float window_height) {
    glRasterPos2f(((x-((float)img.width*sx/2.0f)))*2.0f-1.0f, (1.0f-(y+((float)img.height*sy/2.0f))/(float)window_height)*2.0f-1.0f);
    glPixelZoom(sx, sy);
    draw_cached_img(img);
    return true;
}
