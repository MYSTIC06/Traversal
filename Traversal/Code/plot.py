import matplotlib.pyplot as plt

# Lire les valeurs exportées par le programme C++
with open("valeurs.txt", "r") as fichier:
    V = [int(ligne) for ligne in fichier]

#V.sort()
# Tracer le graphique
plt.plot(V, linestyle="None", marker=".")

plt.xlabel("Indice")
plt.ylabel("Valeur")
plt.title("Valeurs rangées par ordre croissant")
plt.grid(True)

plt.show()