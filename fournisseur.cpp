#include "fournisseur.h"

fournisseur::fournisseur()
{
    id_fournisseur="";
    nom_fournisseur="";
    contact_fournisseur="";
    adresse_fournisseur="";
    date_contract="";
}

void fournisseur:: setid_fournisseur (QString n) {id_fournisseur=n;}
void fournisseur:: setnom_fournisseur (QString n) {nom_fournisseur=n;}
void fournisseur:: setcontact_fournisseur (QString n) {contact_fournisseur=n;}
void fournisseur:: setadresse_fournisseur (QString n) {adresse_fournisseur=n;}
void fournisseur:: setdate_contract (QString n) {date_contract=n;}


QString fournisseur:: get_id_fournisseur(){return id_fournisseur;}
QString fournisseur:: get_nom_fournisseur(){return nom_fournisseur;}
QString fournisseur:: get_contact_fournisseur(){return contact_fournisseur;}
QString fournisseur:: get_adresse_fournisseur(){return adresse_fournisseur;}
QString fournisseur:: get_date_contract(){return date_contract;}

