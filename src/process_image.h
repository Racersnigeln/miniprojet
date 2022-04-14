#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

typedef enum {UNDEFINED, FRANCE} flag;

void process_image_start(void);
flag get_flag(void);    //return UNDIFINED if doesnt find any flag


#endif /* PROCESS_IMAGE_H */
