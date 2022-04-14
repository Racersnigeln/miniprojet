#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

typedef enum {UNDEFINED, FRANCE} Flag;

void process_image_start(void);
Flag get_flag(void);    //return UNDIFINED if doesnt find any flag


#endif /* PROCESS_IMAGE_H */
