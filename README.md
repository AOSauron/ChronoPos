# ChronoPos

**ChronoPos - Application Chronomètre et GPS pour Windows Phone 8.1 minimum**

*Projet de SEP Systèmes Embarqués Portables TELECOM Nancy 2017*

### Site web
Le projet est disponible en open source sur GitHub :
 - [https://github.com/AOSauron/ChronoPos](https://github.com/AOSauron/ChronoPos)

### Auteurs
 - GARCIA Guillaume
 - ZAMBAUX Gauthier

### OS minimal du smartphone
 - Windows Phone 8.1 minimum.

### Dépendances le pour développement sur Windows
 - Windows Phone SDK 8.1
 - Windows 10 minimum
 - Hyper-V activé si Windows 10 est émulé
 - Microsoft Visual Studio 2015 community

### Ouvrir le projet avec Visual Studio
Une fois que Visual Studio 2015 est lancé, ouvrez le fichier `Sources/ProjetSEP.vcxproj` pour charger le projet.

### Principe de l'application
L'application consiste en une interface multithreadée gérant un chronomètre et un GPS. Il y a 3 threads : Le thread principal qui gère l'interface graphique (constituée d'un pivot de 3 vues, d'une map, q'une ScrollViewer pour les données sauvées, un  Textblock "chronomètre" qui s'incrémente), un thread qui s'occupe de gérer le compteur avec un DispatchTimer, et un thread infini lancé dès le début qui initialise le GPS et actualise en temps réel la position.
Le but du développement de cette appli est de nous inicier à la programmation Windows embarquée. L'appli est développée en C++ à partir de Microsoft Visual Studio 2015.

### Présentation du projet
Le support de la soutenance du 11/05/2017 est disponible dans le fichier [Docs/présentation.odp](Docs/présentation.odp)
