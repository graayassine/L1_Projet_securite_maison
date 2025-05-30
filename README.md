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

 Conception et impression 3D et decoupage avec le Laser (FABLAB VALROSE)
 
 Initialement, on a conçu la maison sur Tinkercad pour une impression 3D. Cependant, le temps d'impression était de plus de deux jours, ce qui a rendu cette option impraticable donc on a opté pour une solution plus rapide : la machine de découpe laser. Après la conception initiale, nous avons refait tout le travail d'adaptation pour la découpe.
 
 Installation des composants 
 
 D’abord on a assemblé le circuit avec le capteur PIR, les servos, la LED et le buzzer. Le servomoteur a été fixé mécaniquement au cadre de fenêtre, comme une charnière avec une plage de mouvement de 0° (fermé) à 90° (ouvert). Le capteur PIR placé au dessus de la porte pour éviter les déclenchements par animaux tout en captant bien les mouvements de personnes. Un premier code Arduino a permis de tester chaque composant sans LoRaWAN pour vérifier leur bon fonctionnement. Une fois le circuit validé, on a intégré le module LoRa pour la suite. 
 
 Configuration LoRaWAN 
 
 Le module LoRaWAN a été configuré en mode ABP via The Things Network (TTN), avec les clés DevAddr, NwkSKey et AppSKey programmées dans l'Arduino. Une application mobile a aussi été configurée avec le protocole MQTT pour recevoir les données du capteur transmises via le réseau LoRa, en se connectant directement au serveur de TTN. Ensuite on a développé un second code pour envoyer des alertes via LoRaWAN (mode ABP) et les recevoir sur smartphone. Après des tests réussis, on a fusionné les deux codes pour obtenir la version finale, combinant détection locale et notifications à distance.

 <img width="596" alt="schema_tinker" src="https://github.com/user-attachments/assets/d0e772a3-8cb8-410a-a24d-4bc08d1622e0" /> 
 
 # Architecture du systeme

- Détection : Le capteur PIR scanne en permanence son environnement. Lorsqu’un mouvement est détecté, il envoie un signal à l’Arduino.
       
- Action locale : L’Arduino déclenche immédiatement les actionneurs: Buzzer (alarme sonore) , LED (signal lumineux) , Moteurs (simulation d’une fenêtre qui se ferme)
       
- Alerte à distance : Le module LoRa transmet sans fil l’alerte à un récepteur. Ce dernier relaie la notification vers un smartphone .
       
<img width="529" alt="Capture d’écran 2025-05-29 235318" src="https://github.com/user-attachments/assets/d5eb1913-485f-44a6-96b7-2c3d2a3f65e5" />


