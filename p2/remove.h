#ifndef _REMOVE_H_
#define _REMOVE_H_

#include "paragem.h"
#include "carreira.h"

int *remove_carreira(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int *locations_p);
int *remove_paragem(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int *locations_p);


#endif