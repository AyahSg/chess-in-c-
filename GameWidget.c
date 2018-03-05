/*
 * GameWidget.c
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */


#include <stdio.h>
#include <stdlib.h>
#include "GameWidget.h"

void destroyGameWidget(GameWidget* src) {//Making NULL Safe Destroy
	if (src == NULL ) {
		return;
	}
	src->destroyGameWidget(src);
}
