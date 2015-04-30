/*
 * geom.c
 * Funções geométricas para TADs ponto, retangulo, e círculo.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. F. Lima, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "geom.h"
#include <math.h>

// Funções

// retorna a distancia entre dois pontos
float distancia(ponto_t a, ponto_t b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// retorna true se o ponto estiver dentro do circulo, false caso contrario
bool ptemcirc(ponto_t p, circulo_t c){
	return (distancia(p, c.centro) <= c.raio)?true:false;
}

// retorna true se o ponto estiver dentro do retangulo
bool ptemret(ponto_t a, retangulo_t r){
    return (a.x >= r.pos.x && a.x <= r.pos.x + r.tam.larg && a.y >= r.pos.y && a.y <= r.pos.y + r.tam.alt)?true:false;
}

// retorna true se houver uma interseccao entre o circulo e o retangulo
bool intercr(circulo_t c, retangulo_t r){
    ponto_t ponto1, ponto2, ponto3;
    ponto1.x = r.pos.x + r.tam.larg;
    ponto2.y = r.pos.y + r.tam.alt;
    ponto3.x = r.pos.x + r.tam.larg;
    ponto3.y = r.pos.y + r.tam.alt;
    if(c.centro.x <= r.pos.x + r.tam.larg + c.raio && c.centro.x >= r.pos.x - c.raio 
    && c.centro.y <= r.pos.y + r.tam.alt + c.raio && c.centro.y >= r.pos.y - c.raio){
    	if(distancia(r.pos, c.centro) <= c.raio || distancia(ponto1, c.centro) <= c.raio 
    	|| distancia(ponto2, c.centro) <= c.raio || distancia(ponto3, c.centro) <= c.raio){
    		return true;
    	}
    }else{
    	return false;
    }
}

// retorna true se houver uma interseccao entre os dois retangulos
bool interrr(retangulo_t r1, retangulo_t r2){
	ponto_t centro1, centro2;
	float x, y;
	centro1.x = r1.pos.x + r1.tam.larg/2;
	centro1.y = r1.pos.y + r1.tam.alt/2;
	centro2.x = r2.pos.x + r2.tam.larg/2;
	centro2.y = r2.pos.y + r2.tam.alt/2;
	x = centro1.x - centro2.x;
	y = centro1.y - centro2.y;
	if(x < 0) x *= -1;
	if(y < 0) y *= -1;
    return (x <= r1.tam.larg/2 + r2.tam.larg/2 && y <= r1.tam.alt/2 + r2.tam.alt/2)?true:false;
}

// retorna true se houver uma interseccao entre os dois circulos
bool intercc(circulo_t c1, circulo_t c2){
    return (distancia(c1.centro, c2.centro) <= c1.raio + c2.raio)?true:false;
}