## Réponse aux questions. (PARTIE 1)

1) Cela dépend. En effet, l'utilisation des threads peut-être très utile, cependant si la tâche à réaliser est simple, ne pas diviser en plusieurs threads sera plus efficace et plus rapide. Dans notre cas, la version séquentielle est moins rapide car notre nombre est grand.

2) Plus la valeur de MULTIPLICATEUR est importante, plus l'execution sera lente. La différence est minime car elle se compte en milli-secondes. 

3) Oui, les résustats sont identiques pour les deux versions. Il n'y a pas de race condition car les threads ne modifient pas la même variable et ne touche pas à la zone critique.

4) Voir le fichier resultats.csv

5) Tests effectués : 
    
    - 1 --> 126000 ms
    - 10 --> 36000 ms
    - 100 --> 91000 ms
    - 1000 --> Trop long
    - 10000 --> Trop long
    - 100000 --> Trop long
    - 1000000 --> Trop long

6) Après avoir executé la commande /proc/cpuinfo, je visualise que mon ordinateur possède un processeur de 2 coeurs.

7) Si on initialise 100 threads pour 10 valeurs, il va y avoir un gaspillage de performances car 90 threads n'auront aucune valeur à modifier.

8) Voir image : "Nb threads.png"

Tableau correspondant : 
![alt text](image.png)

## Réponse aux questions. (PARTIE 2)

Observation Typique : Quand il y a un nombre de threads important, il modifient la même variable dans le code compteur_dangereux. Ce qui donne une perte considérable. Donc plus le nombre de threads est élevé plus il y aura de pertes.

Experimentation avec 1/10/50/100

### Avec 1 :

=== Compteur Dangereux ===
Valeur attendue : 11111111
Résultat final : 11111111
Différence : 0

### Avec 10 :

=== Compteur Dangereux ===
Valeur attendue : 111111110
Résultat final : 19776682
Différence : 91334428

### Avec 50 :

=== Compteur Dangereux ===
Valeur attendue : 555555550
Résultat final : 20753922
Différence : 534801628

### Avec 100 :

=== Compteur Dangereux ===
Valeur attendue : 1111111100
Résultat final : 25136577
Différence : 1085974523

- Avec 1 on est donc toujours correct.
- Après avoir modifié le nombre d'incréments, on peut constater que leur nombre d'erreurs varient en fonction de l'incrément.

- Après l'execution de l'optimisation, j'obtiens tout le temps le résustat suivant : 

=== Compteur Dangereux ===
Valeur attendue : 11111100
Résultat final : 11111100
Différence : 0