/*
	<GraphenBibliothek>
	Copyright(C) < 2019 > <Yannick Luc Schmetz>

	This program is free software : you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#include "Kante.h"

Kante::Kante()
{
	this->links = nullptr;
	this->rechts = nullptr;
	richtung = ungerichtet;
	this->gewicht = 0.0;
	this->flusswert = 0.0;
	this->obereKapazit�t = 0.0;
	this->resKante = false;
}

Kante::Kante(shared_ptr<Knoten> links, shared_ptr<Knoten> rechts, int richtung/*=0*/, double gewicht/*=0.0.*/)
{
	this->links = links;
	this->rechts = rechts;
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
	this->gewicht=gewicht;
	this->flusswert = 0.0;
	this->obereKapazit�t = 0.0;
	this->resKante = false;
}

Kante::Kante(shared_ptr<Knoten> links, shared_ptr<Knoten> rechts, int richtung, double gewicht, double kapa, double flussert, bool resKante)
{
	this->links = links;
	this->rechts = rechts;
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
	this->gewicht = gewicht;
	this->flusswert = flussert;
	this->obereKapazit�t = kapa;
	this->resKante = resKante;
}

shared_ptr<Knoten> Kante::getLinks()
{
	return links;
}

shared_ptr<Knoten> Kante::getRechts()
{
	return rechts;
}

int Kante::getRichtung()
{
	return richtung;
}

double Kante::getGewicht()
{
	return this->gewicht;
}

double Kante::getKapazit�t()
{
	return this->obereKapazit�t;
}

bool Kante::getResidualNatur()
{
	return this->resKante;
}

shared_ptr<Kante> Kante::getResidualKante()
{
	return this->residualKante;
}

double Kante::getFlusswert()
{
	return this->flusswert;
}

void Kante::setLinks(shared_ptr<Knoten> l)
{
	this->links = shared_ptr<Knoten>(l);
}

void Kante::setRechts(shared_ptr<Knoten> r)
{
	this->rechts = shared_ptr<Knoten>(r);
}

void Kante::setRichtung(int richtung)
{
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
}

void Kante::setGewicht(double gewicht)
{
	this->gewicht = gewicht;
}

void Kante::setKapazit�t(double kapa)
{
	this->obereKapazit�t = kapa;
}

void Kante::setResidualKante(shared_ptr<Kante> k)
{
	this->residualKante = k;
}

void Kante::setFlusswert(double fluss)
{
	this->flusswert = fluss;
}
