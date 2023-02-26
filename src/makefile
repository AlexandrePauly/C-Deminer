CC = gcc -Wall#Commande de compilation
RM = rm -f#Effacement des fichiers
SRC = $(wildcard $(srcdir)*.c)#Fichiers sources
HEAD = $(wildcard $(srcdir)*.h)#Fichiers principaux
OBJ = $(subst $(srcdir), $(bindir),$(SRC:.c=.o))#Fichiers objets
PROG = exe#Programme final
srcdir = #$(wildcard /src/)#Répertoire qui contient les sources et les en-têtes du projet
bindir = #$(wildcard /bin/)#Répertoire qui contient les objets et exécutables du projet
docdir = #$(wildcard /doc/)#Répertoire qui contient la documentation technique du projet
savedir = #$(wildcard /save/)#Répertoire qui contient les fichiers de sauvegarde du projet
DOXY = doxygen#Doxyfile
CP = cp#Commande pour copie run fichier
MK = mkdir#Commande pour créer un dossier
MV = mv#Commande pour déplacer une source
RM = rm#Commande pour supprimer un dossier
DATE = `date +%Y%m%d`#Date du jour
FIL = doc save bin src#Liste de dossiers
DOX = html latex Doxyfile#Liste de dossiers/fichiers
TOUCH = touch#Commande pour créer un fichier vide
TAR = tar#Commande pour ziper un dossier

all : $(PROG)

#Compilation du programme :

$(PROG) : $(OBJ)
	$(CC) $^ -o $@ -lm

#Compilation des objets :

%.o : ./src/%.c
	$(CC) -c $^ -o $@ -lm

.PHONY : clean doxy cleanDoxy readme save bin restore give ungive files cleanFiles

#Effacement des objets :

clean:
	$(RM) -f $(OBJ) $(PROG)

#Génération de la doxyfile :
	
doxy:
	$(DOXY) -g
	$(DOXY) Doxyfile
	$(MK) -p doc
	$(MV) $(DOX) doc

#Suppression de la doxyfile :

cleanDoxy:
	$(RM) -r doc/*

#Générer le README

readme :
	$(TOUCH) README
	$(MV) README doc

#Sauvegarde des fichiers sources : 

save:
	$(MK) -p save/src_$(DATE)
	$(CP) -r $(SRC) save/src_$(DATE)
	$(CP) -r $(HEAD) save/src_$(DATE)

#Sauvegarde des fichiers exécutables :

bin:
	$(MV) $(OBJ) bin

#Copie des fichiers de save vers src

restore:
	$(CP) -r save/src_$(DATE)/* src

#Crée un fichier compressé de la dernière sauvegarde

give:
	$(MK) -p paulyalexa-tpX/doc paulyalexa-tpX/src
	$(CP) doc/Doxyfile paulyalexa-tpX/doc
	$(CP) doc/README paulyalexa-tpX
	$(CP) makefile paulyalexa-tpX/src
	$(CP) src/* paulyalexa-tpX/src
	$(TAR) -cvf paulyalexa-tpX.tar paulyalexa-tpX

#Décompresse un fichier

ungive:
	un$(ZIP) paulyalexa-tpX.zip 

#Crée les dossiers doc, save, bin et src

files :
	$(MK) -p $(FIL)

#Supprime les dossiers doc, save, bin et src

cleanFiles :
	$(RM) -r $(FIL)
