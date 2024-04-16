LEARN GIT : https://learngitbranching.js.org/?locale=fr_FR


                            Documentation pour les fonctions :


Gestion des lignes recu en prompt :

readline () lis le prompt et stock dans un char *

rl_on_new_line ()

rl_replace_line ()

add_history () sauvegarde des lignes 

rl_clear_history () vide l'historique

rl_redisplay () affiche une ancienne ligne
    
      https://tiswww.case.edu/php/chet/readline/readline.html


Gestion de process :

pipe () Créer un tube dans un sens de communication

      http://manpagesfr.free.fr/man/man2/pipe.2.html
      
execve () execute un programme, une commande de shell par exemple

      http://manpagesfr.free.fr/man/man2/execve.2.html

dup () Dupliquer un descripteur de fichier

dup () transforme newfd en une copie de oldfd

      https://www.man-linux-magique.net/man2/dup2.html

wait() attend jusqu'a que l'un de ses fils est termine

waitpid() attend jusqu'a que le process specifie est termine

      https://www.man-linux-magique.net/man2/waitpid.html

wait3() attend n’importe quel fils

wait4() attend un ou des fils spécifique(s)

      https://www.man-linux-magique.net/man2/wait3.html
fork() creation d'une copie du process

      http://manpagesfr.free.fr/man/man2/fork.2.html

ioctl() modifie des process, permet de controler un terminal

      http://manpagesfr.free.fr/man/man2/ioctl.2.html


Gestion des signaux :

signal() reception de signaux

sigaction() reception de signaux stocke dans une structure

sigemptyset() initialise les signaux

sigaddset() ajoute et supprime les signum

    https://linux.die.net/man/3/sigemptyset

    
Gestion des document :

access () verifircation des droits du process appelant

      https://linux.die.net/man/2/access

getcwd () retourne un char * du directory du process appelant

      https://man7.org/linux/man-pages/man3/getcwd.3.html

chdir () change de directory a celui specifie

      https://man7.org/linux/man-pages/man2/chdir.2.html

opendir() Ouvrir un répertoire  

      https://man7.org/linux/man-pages/man3/opendir.3.html

readdir() Read a directory

      http://manpagesfr.free.fr/man/man3/readdir.3.html

closedir () close dir

      https://man7.org/linux/man-pages/man3/closedir.3.html

stat () récupèrent des renseignements sur le fichier pointé par pathname

lstat () comme stat mais avec un lien symbolique

fstat () comme stat() mais avec un fd

      https://fr.manpages.org/stat/2
      
unlink () Détruire un nom et éventuellement le fichier associé

      http://manpagesfr.free.fr/man/man2/unlink.2.html


Gestion Des Erreurs :

strerror() decrit le code d'erreur passe en argument

      http://manpagesfr.free.fr/man/man3/strerror.3.html
      
perror()  Afficher un message d'erreur système 

      http://manpagesfr.free.fr/man/man3/perror.3.html
      
isatty() verifie si le fd est ouvert

      http://manpagesfr.free.fr/man/man3/isatty.3.html
      
ttyname() Renvoie le path d'un fd

      http://manpagesfr.free.fr/man/man3/ttyname.3.html
      
ttyslot()  renvoie la position de l'entrée du terminal en cours dans un fichier

      http://manpagesfr.free.fr/man/man3/ttyslot.3.html
      
getenv() donne la valeur d'une variable d'environnement

      http://manpagesfr.free.fr/man/man3/getenv.3.html

tcgetattr() récupère les paramètres associés à l'objet référencé par fd

tcsetattr() fixe les paramètres du terminal 

      http://manpagesfr.free.fr/man/man3/termios.3.html


Sous-Routine :

tgetent()

tgetflag()

tgetnum()

tgetstr()

tgoto()

tputs()

      https://linux.die.net/man/3/tgetent
