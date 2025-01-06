# TP_de_Synthese_2

Pour ce second TP, nous avons repris pendant les vacances le travail commencé en séance afin de restructurer les codes.
Nous avons ainsi séparer les différentes fonctions en les appelant dans un main. 

Lors de la première séance, nous avons mis du temps à comprendre ce qu'on attendait exactement.

On réussit à obtenir l'adresse via getaddrinfo() assez simplement en faisant l'analogie avec le TD.

On à pris du temps à bien comprendre comment utiliser le serveur. Au final on arrive à créer le socket. 

On crée la request rrq et on l'envoie sur le serveur. On constate avec wireshark qu'on a bien un envoie de notre ordinateur, auquel le serveur nous renvoie un message, mais pas avec le même port que celui où il a reçu la requête. 

Nous sommes à l'étape du ACK. 
