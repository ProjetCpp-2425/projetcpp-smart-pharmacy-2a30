#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>

class fournisseur
{
public:
    void setid_fournisseur(QString n);
    void setnom_fournisseur(QString n);
    void setcontact_fournisseur(QString n);
    void setadresse_fournisseur(QString n);
    void setdate_contract(QString n);

    QString get_id_fournisseur();
    QString get_nom_fournisseur();
    QString get_contact_fournisseur();
    QString get_adresse_fournisseur();
    QString get_date_contract();
    fournisseur();

private:
    QString id_fournisseur,nom_fournisseur,contact_fournisseur,adresse_fournisseur,date_contract;
};

#endif // FOURNISSEUR_H
