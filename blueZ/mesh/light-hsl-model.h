/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   light-hsl-model.h
 * Author: ledvance
 *
 * Created on February 8, 2018, 5:56 PM
 */

#define HSL_CLIENT_MODEL_ID                     0x1309

#define OP_LIGHT_HSL_GET			0x826D
#define OP_LIGHT_HSL_SET			0x8276
#define OP_LIGHT_HSL_STATUS                     0x8278


void lighting_set_node(const char *args);
bool hsl_client_init(uint8_t ele);
