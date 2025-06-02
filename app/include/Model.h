

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

    /**
     * @brief Récupère un utilisateur à partir de sa clé d'identification.
     * 
     * @param key Clé unique associée à un utilisateur (ex : identifiant, token d'authentification).
     * @return User Objet représentant l'utilisateur correspondant à la clé fournie.
     * 
     * @details
     * Cette méthode permet d'accéder aux informations d'un utilisateur identifié par une clé donnée.
     * Elle est utile notamment après une authentification réussie ou pour manipuler des données liées à un utilisateur.
     * En cas de clé invalide ou inconnue, la méthode lève une exception.
     */
    User GetUser(string key);

    
        /**
     * @brief Récupère un capteur à partir de son identifiant.
     * 
     * @param sensorId Identifiant unique du capteur recherché.
     * @return Sensor Objet représentant le capteur correspondant à l'identifiant donné.
     * 
     * @details
     * Cette méthode permet d'accéder à un capteur spécifique en fournissant son identifiant.
     * Une exception peut être retournée si l'identifiant est invalide.
     */
    Sensor getSensor(string sensorId);


    /**
     * @brief Récupère l'ensemble des capteurs disponibles.
     * 
     * @return map<string, Sensor> Dictionnaire associant les identifiants de capteurs à leurs objets respectifs.
     * 
     * @details
     * Cette méthode fournit un accès à tous les capteurs enregistrés dans les fichiers CSV fournis.
     * Elle est utile pour effectuer des opérations globales comme le calcul de statistiques par zone ou la comparaison des capteurs .
     */
    map<string, Sensor> getAllSensors();



    /**
     * @brief Récupère un nombre limité de mesures d'un capteur pour un attribut donné.
     * 
     * @param sensorId Identifiant du capteur concerné.
     * @param count Nombre de mesures à récupérer (les plus récentes ou selon un ordre défini).
     * @param attribute Nom de l'attribut mesuré (ex : "O3", "NO2", etc.).
     * @return vector<Measurement> Liste de mesures correspondant au capteur et à l'attribut spécifiés.
     * 
     * @details
     * Cette méthode permet de récupérer rapidement un échantillon de mesures récentes
     * pour un capteur donné et un polluant spécifique, ce qui est utile pour l'affichage
     * en temps réel et les calculs.
     */
    vector<Measurement> getMeasurements(string sensorId, int count, string attribute); 


    /**
     * @brief Récupère toutes les mesures d’un capteur pour un attribut donné.
     * 
     * @param sensorId Identifiant du capteur concerné.
     * @param attribute Nom de l'attribut mesuré (ex : "PM10", "SO2", etc.).
     * @return vector<Measurement> Liste complète des mesures du capteur pour cet attribut.
     * 
     * @details
     * Cette méthode donne accès à l’historique complet des mesures d’un capteur pour un polluant donné.
     * Elle est particulièrement utile pour les analyses statistiques ou les comparaisons inter-capteurs.
     */
    vector<Measurement> getMeasurements(string sensorId, string attribute) ; 


    /**
     * @brief Récupère tous les utilisateurs enregistrés.
     * 
     * @return vector<User> Liste de tous les utilisateurs présents dans le système.
     * 
     * @details
     * Cette méthode permet d’accéder aux informations concernant l’ensemble des utilisateurs,
     * ce qui peut être utile pour des opérations de gestion (vérification d'identité, attribution de capteurs, etc.)
     * ou pour des analyses basées sur les profils d'utilisateurs (fiabilité,etc.).
     */
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
    /**
     * @brief Compares a given sensor to all other loaded sensors and computes a similarity score.
     * 
     * @param referenceSensorID ID of the reference sensor.
     * @param startDate Start date of the comparison period.
     * @param endDate End date of the comparison period.
     * @return std::vector<std::pair<std::string, double>> A sorted vector of pairs (sensor ID, similarity score),
     *         containing up to the 5 most similar sensors, ordered by descending similarity.
     * 
     * @details
     * This method analyzes the measurements of the reference sensor over the specified time range
     * and compares them with measurements from all other loaded sensors.
     * 
     * For each sensor, a similarity score is computed based on the proximity of measured values.
     * The result is a sorted list of the most similar sensors:
     *   - Each entry is a pair (sensor ID, similarity score).
     *   - The list is sorted in descending order of similarity score.
     *   - Only the top 5 most similar sensors are included in the result.
    */


    double calculateSimilarity(const Sensor& referenceSensor, const Sensor& compareSensor, const Date& startDate, const Date& endDate);
    /**
     * @brief Calculates a similarity score between two sensors based on the average of their measurements.
     * 
     * @param referenceSensor The reference sensor to compare against.
     * @param compareSensor The sensor being compared to the reference sensor.
     * @param startDate Start date of the measurement period.
     * @param endDate End date of the measurement period.
     * @return double A similarity score between 0.0 and 100.0, where a score closer to 100 indicates higher similarity.
     * 
     * @details
     * The method compares the average values of the following four attributes: O3, NO2, SO2, and PM10.
     * Only measurements within the specified date range are considered.
     * 
     * For each attribute, the method computes the average for both sensors, then calculates a normalized similarity score.
     * The final result is a global similarity score:
     *   - Ranges from 0.0 (no similarity) to 100.0 (identical average values).
     *   - Higher values indicate stronger similarity between the two sensors' measurements.
    */


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

    /**
     * @brief Charge les données des capteurs, mesures et attributs depuis des fichiers CSV.
     * 
     * @param pathSensorCSV Chemin du fichier CSV contenant les informations des capteurs.
     * @param pathMeasureCSV Chemin du fichier CSV contenant les mesures des capteurs.
     * @param pathAttributeCSV Chemin du fichier CSV contenant les attributs (type de polluants, unités, etc.).
     * @return true Si l'ensemble des fichiers ont été correctement lus et chargés.
     * @return false En cas d'erreur de lecture, de format invalide ou de données manquantes.
     * 
     * @details
     * Cette méthode initialise les données du système en important les capteurs, leurs mesures et les types d’attributs associés.
     * Elle vérifie également la cohérence entre les fichiers (par exemple, mesures associées à un capteur existant).
     * Utile à l'initialisation de l'application pour permettre les traitements ultérieurs (analyses, visualisations).
     */
    bool loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV);

    /**
     * @brief Charge les données des purificateurs d’air à partir d’un fichier CSV.
     * 
     * @param pathCleanerCSV Chemin du fichier CSV contenant les informations sur les purificateurs.
     * @return true Si les données sont chargées avec succès.
     * @return false En cas d’erreur de lecture ou de format incorrect.
     * 
     * @details
     * Cette méthode permet d’ajouter les données relatives aux dispositifs de purification d’air,
     * tels que leur localisation, et durée d’activité. Ces données sont ensuite
     * utilisées pour modéliser leur impact sur la qualité de l’air locale.
     */
    bool loadCleaners(string pathCleanerCSV);

    /**
     * @brief Charge les données des utilisateurs et des fournisseurs depuis des fichiers CSV.
     * 
     * @param pathUserCSV Chemin du fichier CSV contenant les informations des utilisateurs.
     * @param pathProviderCSV Chemin du fichier CSV contenant les informations des fournisseurs.
     * @return true Si toutes les données sont chargées correctement.
     * @return false En cas d’erreur de lecture, de format ou d’incohérence entre les fichiers.
     * 
     * @details
     * Cette méthode initialise les profils des utilisateurs du système.. 
     */
    bool loadUsersData(string pathUserCSV, string pathProviderCSV);

    /**
     * @brief Évalue si un capteur est considéré comme fiable.
     * 
     * @param sensorId Identifiant du capteur à évaluer.
     * @return true Si le capteur est jugé fiable.
     * @return false Si le capteur présente des incohérences, erreurs ou comportements suspects.
     * 
     * @details
     * Cette méthode permet de filtrer les capteurs dont les données peuvent être utilisées pour des analyses précises.
     * Elle peut se baser sur des critères tels que la régularité des mesures, la cohérence par rapport aux capteurs voisins,
     * ou encore des signalements d’anomalies. Les capteurs non fiables peuvent être exclus des calculs statistiques.
     */
    bool isSensorReliable(string sensorId);

    /**
         * @brief Vérifie si un point géographique se situe dans un rayon donné autour d’un autre point.
         * 
         * @param lat1 Latitude du point de référence (en degrés).
         * @param lon1 Longitude du point de référence (en degrés).
         * @param lat2 Latitude du point cible (en degrés).
         * @param lon2 Longitude du point cible (en degrés).
         * @param radiusKm Rayon à considérer (en kilomètres).
         * @return true Si le point (lat2, lon2) se trouve à une distance inférieure ou égale à radiusKm de (lat1, lon1).
         * @return false Sinon.
         * 
         * @details
         * Cette méthode utilise une formule de distance géographique (typiquement la formule de Haversine)
         * pour déterminer si deux localisations sont proches. Elle est utile pour la recherche de capteurs ou purificateurs
         * dans un périmètre donné autour d’un utilisateur ou d’un événement.
     */
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
