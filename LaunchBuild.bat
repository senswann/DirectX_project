@echo off

rem Nom du dossier à créer
set "nom_dossier=Build"

rem Vérifier si le dossier existe déjà
if exist "%nom_dossier%" (
    echo Le dossier "%nom_dossier%" existe déjà.
    rem Supprimer le dossier
    rmdir /s /q "%nom_dossier%"
) 
mkdir "%nom_dossier%"

rem Entrer dans le dossier créé
cd "%nom_dossier%"

rem Exécution des commandes suivantes dans le dossier Build
cmake ../App
cmake --build .

rem Message facultatif (vous pouvez le supprimer si vous ne souhaitez pas afficher de message)
echo Tâches terminées.