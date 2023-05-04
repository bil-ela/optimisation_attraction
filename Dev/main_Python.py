# Ouverture fichier CSV
import csv
import numpy as np


#Fonction qui permet de connaître le nombre d'individu dans une liste.
def somme_premier_element(liste):
    somme = 0
    del(liste[0])
    for l in liste:
        somme += int(l[0][0])
    return somme

#Fonction répartition expliqué dans le PDF
def repartition (grande_liste,maximum_personnes):
    deux=[]
    trois=[]
    quatre=[]
    cinq=[]
    six=[]
    P=[]
    # 1ère boucle
    # J correspond est une liste qui renvoie le nombre de présent chaque jour de la semaine dans le parc
    J=[0,0,0,0,0,0,0]
    for i in range(len(grande_liste)):
        if J[grande_liste[i][1]] < maximum_personnes:
            grande_liste[i].append(1)
            P.append(grande_liste[i])
            J[grande_liste[i][1]] += grande_liste[i][0]
        else:
            deux.append(grande_liste[i])
    # 2ème boucle
    for i in range(len(deux)):
        if J[deux[i][2]] < maximum_personnes:
            deux[i].append(2)
            P.append(deux[i])
            J[deux[i][2]] += deux[i][0]
        else:
            trois.append(deux[i])
    # 3ème boucle
    for i in range(len(trois)):
        if J[trois[i][3]] < maximum_personnes:
            trois[i].append(3)
            P.append(trois[i])
            J[trois[i][3]] += trois[i][0]
        else:
            quatre.append(trois[i])
    # 4ème boucle
    for i in range(len(quatre)):
        if J[quatre[i][4]] < maximum_personnes:
            quatre[i].append(4)
            P.append(quatre[i])
            J[quatre[i][4]] += quatre[i][0]
        else:
            cinq.append(quatre[i])
    # 5ème boucle
    for i in range(len(cinq)):
        if J[cinq[i][5]] < maximum_personnes:
            cinq[i].append(5)
            P.append(cinq[i])
            J[cinq[i][5]] += cinq[i][0]
        else:
            # Normalement cette liste doit rester vide
            six.append(cinq[i])
    return P,J

            
#Fonction qui permet de calculer le coût engendré par une famille
def fonction_cout_1famille(L):
    #On rappelle que la dernière colonne représente l'affectation au jour choisi à la famille
    #On note C le coût d'une famille
    c = 0
    if L[len(L)-1] == 2:
            c=c+50
    elif L[len(L)-1] == 3:
            c=c+50+(9*L[0])
    elif L[len(L)-1] == 4:
            c=c+100+(9*L[0])
    elif L[len(L)-1] == 5:
            c=c+200+(9*L[0])
    else:
            c=c+0        
    return c

#Fonction qui permet de calculer le coût de toutes les familles
def cout_total(M):
    #On note C le coût total
    c = 0
    for i in range(len(M)):
        c=c+fonction_cout_1famille(M[i])
    return c

#Fonction qui permet de calculer les pénalités
def penalite(liste_J):
    p=0
    for i in range (len(liste_J)):
        if i <= 5:
            p += (((liste_J[i] - 125) / 400) * liste_J[i]) ** (abs(liste_J[i] - liste_J[i + 1]) / 50)
        else:
            p += (((liste_J[i] - 125) / 400) * liste_J[i])
    return p


#Ouverture des fichiers .csv
with open('emplacement_du_fichier', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    data = [row for row in reader]
    

matrice = np.array(data)
matrice = matrice.tolist()
matrice_3=[]
del(matrice[0])
for i in range(len(matrice)):
    matrice_3.append([int(x) for x in matrice[i][0].split(";")])

somme = somme_premier_element(matrice)
MV2, Population_Semaine = repartition(matrice_3,270)
print(repartition(matrice_3,270))
print(cout_total(MV2))
print(penalite(Population_Semaine))
