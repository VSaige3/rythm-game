/**
 * NoteManager
 * Handles reading notes and storing them
 */

/**
 * Format Specs:
 * starts with bpm in header
 * 
 * then each note with header, owner# & type
 * Next is position and length
 * 
 * position stored as measure, then division of a beat, then number of those from measure beginning.
 * length is the number of the same subdivisions the note lasts for
 * 
 *
 * 
 */

/**
 * will make 2 formats - one readable, one compressed
 * (do readable later)
 */

/*
 - TODO:
 - make a way to edit/store test charts
 - read the files
 - 
*/



struct chart {

};

int serialize_chart(struct chart chart);
int deserialize_chart(struct chart *chart, char *data, int length);

char *uncompress_chart(struct chart chart);
int compress_chart(struct chart *chart, char *data, int length);
