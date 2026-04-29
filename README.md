# My-Top

> **⚠️ Avertissement Epitech**
>
> Ce projet a été réalisé dans le cadre du cursus **Epitech**. Il est **strictement interdit** de s'en inspirer, de le copier ou de le réutiliser à des fins de triche. Tout plagiat sera sanctionné selon la politique de l'école (-42). 

## Description

`My-Top` est une recréation basique de la célèbre commande Unix `top`. Ce programme permet de surveiller en temps réel l'activité du système, incluant :
- L'uptime, load average et le nombre d'utilisateurs connectés
- Les statistiques en temps réel du CPU
- L'utilisation de la mémoire (RAM et Swap)
- La liste des processus en cours d'exécution et des informations détaillées 

Le projet est écrit en **C** et s'appuie sur la bibliothèque **ncurses** pour l'interface de terminal.

## Installation

Pré-requis :
- Compilateur `clang`
- Bibliothèque `ncurses` (`libncurses-dev` ou équivalent selon la distribution)
- Utilitaire `make`

Pour compiler le projet, exécutez simplement la commande `make` à la racine du dossier :

```bash
make
```

Ceci générera l'exécutable `my_top`.

D'autres commandes Make sont disponibles :
- `make clean` : Supprime les fichiers objets et temporaires.
- `make fclean` : Supprime les fichiers générés ainsi que l'exécutable final.
- `make re` : Ré-exécute les commandes `fclean` suivie de `all`.
- `make valgrind` : Compile le projet avec des options de débogage pour Valgrind.

## Utilisation

Une fois compilé, vous pouvez lancer le programme de base :

```bash
./my_top
```

### Options

Il est possible de configurer le comportement de la commande `my_top` via plusieurs arguments :

- `-d <délai>` : Spécifie le délai en secondes entre chaque rafraîchissement de l'écran. (ex: `./my_top -d 1.5`)
- `-n <itérations>` : Limite le nombre de rafraîchissements (frames) maximum avant que le programme ne se ferme de lui-même. (ex: `./my_top -n 10`)
- `-U <utilisateur>` : Filtre l'affichage des processus pour ne montrer que ceux appartenant à un utilisateur spécifique. (ex: `./my_top -U root`)

Exemple de commande combinant plusieurs flags :
```bash
./my_top -d 2.0 -n 50 -U esp
```
