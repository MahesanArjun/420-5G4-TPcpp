# TP C++ — Gestion de bibliothèque

**Nom :** Arjun Mahesan

## Environnement

Projet réalisé sur **Windows** avec VS Code, Docker Desktop et le dev container C++ de VS Code. Les commandes se tapent dans le terminal de VS Code, à l'intérieur du dev container :

```bash
mkdir build && cd build
cmake ..
make
./bibliotheque -d ../data
```

## Fonctionnalités réalisées

- **`book.cpp`** : reconstruit à partir de `book.h`.
- **Numérotation automatique des ID utilisateurs** *(Interface)* : l'ID du nouvel utilisateur est généré automatiquement (`USR026`, `USR027`).
- **Tri par titre ou par auteur** *(Gestion des données)* : à l'option 5, avec `std::sort`.
- **Journal d'activités** : chaque ajout, suppression, emprunt et retour est enregistré dans `journal.log`, qui est conservé d'une session à l'autre.

## Bugs corrigés

- **Sauvegarde sans `--data-dir`** : le programme ne tente plus de sauvegarder et affiche un message clair.
- **Fins de ligne Windows** : les fichiers de données utilisent des fins de ligne Windows (`\r\n`). Le `\r` restait collé à la fin de chaque ligne, ce qui empêchait de retirer un livre retourné de la liste de l'utilisateur. Il est maintenant retiré à la lecture.
- **Sauvegarde de secours (option 13)** : ne plante plus quand on l'utilise deux fois.

### Question 1 : les pointeurs intelligents (`unique_ptr`)

La classe Library garde ses livres dans un vector<unique_ptr<Book>>. Un unique_ptr est un pointeur intelligent qui est le seul propriétaire de son objet: quand il est detruit, il libère la mémoire toute seule. Par exemple, quand removeBook fait books.erase(it), le livre est supprimé sans écrire de delete, donc il n'y a pas de risque de fuite de mémoire. Pour donner accès à un livre sans en céder la propriété, findBookByISBN retourne un pointeur normal obtenu avec .get().

```cpp
vector<unique_ptr<Book>> books;               // library.h
books.push_back(make_unique<Book>(book));     // addBook: crée le livre
books.erase(it);                              // removeBook: libéré automatiquement
return (it != books.end()) ? it->get() : nullptr;  // findBookByISBN
```

### Question 2 : une solution pour des millions de livres

Avec des millions de livres, tout charger en mémoire et réecrire des fichiers texte à chaque sauvegarde serait beaucoup trop lent. J'utiliserais plutôt une base de données PostgreSQL sur un serveur, avec des tables "livres", "usagers" et "emprunts", et des index sur l'ISBN, le titre et l'auteur pour que les recherches restent rapides. La base de données permet aussi à plusieurs employés de travailler en même temps sans qu'un livre soit emprunté deux fois. Pour la relier au C++, j'utiliserais la bibliothèque libpqxx: les méthodes de "Library" ("findBookByISBN", "checkOutBook") feraient des requêtes SQL au lieu de parcourir un "vector", et la classe "FileManager" ne serait plus necessaire.