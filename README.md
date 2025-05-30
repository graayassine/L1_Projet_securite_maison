# L1_Projet_securite_maison
Ce projet est réalisé dans le cadre du module Communication Sans Fil en Licence 1 à l'Université COTE D'AZUR Campus Valrose au FABLAB 

![IMG_2146](https://github.com/user-attachments/assets/8a179703-d3ef-46bf-a64e-659647569a82)
# Description
 Système de sécurité autonome avec détection PIR, actionneurs et notifications LoRaWAN.
 Détecter les intrusions via  capteurs PIR
  , actionner des servos (fenêtres) et alarme (buzzer/LED)
 et envoyer des alertes sur smartphone via LoRaWAN
 # Composants et materiels 
 Arduino UCA , Capteur PIR , Servo-moteur , LED + Résistance , Buzzer , Breadboard 
 
 # Branchement et realisation
 <img width="596" alt="schema_tinker" src="https://github.com/user-attachments/assets/d0e772a3-8cb8-410a-a24d-4bc08d1622e0" /> 
 
 # Architecture du systeme

- Détection : Le capteur PIR scanne en permanence son environnement. Lorsqu’un mouvement est détecté, il envoie un signal à l’Arduino.
       
- Action locale : L’Arduino déclenche immédiatement les actionneurs: Buzzer (alarme sonore) , LED (signal lumineux) , Moteurs (simulation d’une fenêtre qui se ferme)
       
- Alerte à distance : Le module LoRa transmet sans fil l’alerte à un récepteur. Ce dernier relaie la notification vers un smartphone .
       
<img width="529" alt="Capture d’écran 2025-05-29 235318" src="https://github.com/user-attachments/assets/d5eb1913-485f-44a6-96b7-2c3d2a3f65e5" />


