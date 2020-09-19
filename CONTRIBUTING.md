# 👪 Contributing

This file is a synthesis of the base rule use in the repo.





## 📝Codding guide line

### #️⃣ Versioning

We use [Semantic Versioning](https://semver.org/) : `MAJOR.MINOR.PATCH`:

- `MAJOR` was incremented every **rewrite**
- `MINOR` was incremented every **new feature**
- `PATCH` was incremented every **new fix/patch**

Please modify the `Makefile` after each version change.



### 🌳 Branch structure

- The main branch is `master`.  The `master` is protected you can't push on it, you need to create a new branch and make a [pull request](https://github.com/JulesdeCube/unread/pulls).
- To work in a new version please make a new branch named by the version name (ex : `1.2.12`). Like the `master` branch in version branch you need to make pull request to merge and the code need to be validate by  an other developer.
- Don't directly make commit on the version branch, create a feature/fix branch prefixed by the version name, the modification type and a `/` (ex: `1.2.12/feature/my_feature_name`).



### 🗂️ File structure

- `/src/` : contained all the source (`.c`, `.h`, ...)
- `/src/lib/` : all the external library (*git Ignored*)
- `/build/` : the outputted binary (*git ignored*)
- `/obj/` : compiled files (*git ignored*)



### ✏️ Coding style

use the [**EPITA's C coding style** ](https://ceph.assistants.epita.fr/public-documents.assistants.epita.fr/coding-style-epita.pdf).

:warning:Except the `2.3 braces.indent` rule : We **MUST NOT use a 4 spaces indentation** but **MUST use 2 spaces indentation**

:heavy_plus_sign: All  code **MUST** be commented, otherwise you change can't be accepted and merge



### ⚒️Compilation

To add files into the compilation add they files path in the `SRC` variable of the [`Makefile`](./Makefile) for `.c` files and the `DEPS` variable for `.h` files.





## ↩️Feedback guide line

If you have any problem first please search if the problem is not yet report.

If it is a new problem please create a [new issues](https://github.com/JulesdeCube/unread/issues).



### Issues rules

- a clear description of the problem
- the using version
- a procedure to recreate the problem
- a video or an image if possible