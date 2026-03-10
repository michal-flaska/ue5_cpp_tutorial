# C++ v Unreal Engine 5

Tento tab som pisal ja (Miso). Snazil som sa to napisat co najlepsie, je tu len zaklad. Vsetko dolezite je v GitHub projekte a resources ktore su v nom. Pozri poslednu section v tomto tabe.

## Preco vobec C++?

Blueprinty su ok. Nikto ti nehovori ze ich mas prestat pouzivat. Ale ked zacnes robit komplexnejsie systemy narazis na ich limity

C++ je rychlejsi (kompiluje sa priamo, BP bezi cez VM), mas pristup k veciam ktore BP vobec nevystavi, a text subory sa omnoho lepsie pouzivaju s gitom ako binarky .uasset

Najcastejsi workflow v praxi: logika v C++, hodnoty a vizualna logika v BP (hybrid). Nie bud/alebo

## Co nainstalovat

Visual Studio 2022 - oficialny IDE pre UE.
Pre UE 5.6 a vyssi odporucam Visual Studio 2026 ak je dostupny.

Existuje aj JetBrains Rider (este lepsi pre UE), ale je plateny. Pre studentov je zdarma cez JetBrains Student Program (jetbrains.com/student) ak chcete.

Cely proces instalacie je v prezke: https://www.canva.com/design/DAHCPd5DP4g/5ns5lvuQEocKJFxxAXM-tw/edit?utm_content=DAHCPd5DP4g&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton

Taky friendly note predtym nez vam zacnu crashovat veci:
- UE5.0 - 5.5 pouziva Visual Studio 2022: https://my.visualstudio.com/Downloads?q=Visual%20Studio%202022 (musite sa prihlasit)
- UE5.6 a viac pouziva Visual Studio 2026 (latest)

## Kde sa naucit viac

Vsetko co som nasiel uzitocne (tutorials, dokumentacia, referencie aj samotny funkcny kod) je v github project

GitHub project: https://github.com/michal-flaska/ue5_cpp_tutorial

Ak chcete vidiet C++ v praxi v realnom projekte, nas koncorocny projekt Bomberman3D je pisany v C++: https://github.com/redfox-studios/Bomberman3D