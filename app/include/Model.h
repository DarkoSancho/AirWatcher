

//---------- Interface de la classe <Model> (fichier Model.h) ----------------

#if ! defined ( MODEL_H )
#define MODEL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
#include <vector> 
#include <climits>
using namespace std;

#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"
#include "Date.h"
//------------------------------------------------------------------------

// In order to return statistics from a sensor
struct Stats {
    map<string,float> average;
    map<string,float> minimum;
    map<string,float> maximum;
    map<string,float> sdeviation;
    map<string,float> excedances;
    map<Date,int> atmo;
    pair<Date, int> matmo;
    pair<Date, int> Matmo;
};

class Model

{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    User GetUser(string key);

    Sensor getSensor(string sensorId);
    
    map<string, Sensor> getAllSensors();

    vector<Measurement> getMeasurements(string sensorId, int count, string attribute); 

    vector<Measurement> getMeasurements(string sensorId, string attribute) ; 

    vector<User> getAllUsers();

    Stats getData(string sensorId, Date startDate, Date EndDate, int Th03 = -1, int ThNO2 = -1, int ThSO2 = -1, int ThPM10 = -1);
    /**
     * @brief Calcule et retourne des statistiques sur les mesures d'un capteur donné sur une période spécifiée.
     * 
     * @param sensorId Identifiant du capteur à analyser.
     * @param startDate Date de début de la période d'analyse.
     * @param EndDate Date de fin de la période d'analyse.
     * @param Th03 Seuil optionnel pour l'O3 (par défaut -1, ignoré si négatif).
     * @param ThNO2 Seuil optionnel pour le NO2 (par défaut -1, ignoré si négatif).
     * @param ThSO2 Seuil optionnel pour le SO2 (par défaut -1, ignoré si négatif).
     * @param ThPM10 Seuil optionnel pour le PM10 (par défaut -1, ignoré si négatif).
     * @return Stats Objet contenant les statistiques calculées.
     * 
     * @details
     * La fonction retourne les statistiques suivantes pour chaque composant x :
     *   - average[x] : Concentration moyenne du composant x.
     *   - minimum[x] : Concentration minimale du composant x.
     *   - maximum[x] : Concentration maximale du composant x.
     *   - sDeviation[x] : Écart-type de la concentration du composant x.
     *   - excedances[x] : Nombre de dépassements du seuil pour le composant x.
     *   - matmo : Paire (jour, valeur) correspondant à la valeur ATMO la plus élevée sur la période.
     *   - matmp : Paire (jour, valeur) correspondant à la valeur ATMO la plus basse sur la période.
     * 
     * Cette méthode permet ainsi d'obtenir un résumé statistique complet de la qualité de l'air mesurée par un capteur sur une période donnée.
 */

    vector<pair<string, double>> compareSensors( const string& referenceSensorID, const Date& startDate,  const Date& endDate);

    double calculateSimilarity(const Sensor& referenceSensor, const Sensor& compareSensor, const Date& startDate, const Date& endDate);
    //Retun statistiques: 
    //result.average[x]: Average concentration of x component
    //result.minimum[x]: mininimum concentration of x component
    //result.maximum[x]: maximum concentration of x component
    //result.sDeviation[x]: Standard deviation of component x
    //result.excedances[x]: Numeros of excedance of component x
    //result.matmo: Pair of Day and value of highest ATMO value
    //result.matmp: Pair of Day and value of lowest ATMO value


    //surcharge de clauclate similarity 
    double calculateSimilarity(const vector<Measurement>& ref, const vector<Measurement>& cmp) ; 


//-------------------------------------------- Constructeurs - destructeur
    Model ( );

    virtual ~Model ( );

    bool loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV);
 
    bool loadCleaners(string pathCleanerCSV);

    bool loadUsersData(string pathUserCSV, string pathProviderCSV);

    bool isSensorReliable(string sensorId);

    bool isWithinRadius(float lat1, float lon1, float lat2, float lon2, float radiusKm) ; 

    vector<float> airQualityGeo (float latitude , float longitude ,  Date start_date , Date end_date ,float radius =0 ) ;  

    float calculateDistance(float lat1, float lon1, float lat2, float lon2);

    vector<Measurement> getAllMeasurementsForAttribute(string attribute);

//------------------------------------------------------------------ PRIVE


//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
protected:
map<string,Sensor> sensors; 
map<string,Attribute> attributes;
map<string,vector<Measurement>> measurements;
map<string,Provider> providers;
map<string,Cleaner> cleaners;
map<string,User> users;

};

//-------------------------------- Autres définitions dépendantes de <Model>

#endif // MODEL_H;
