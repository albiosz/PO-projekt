Vim like backend - instrukcja użytkowania - W RAZIE BRAKÓW ALBO BŁĘDÓW W KODZIE PISZCIE NA FB ;)

0. Kompilacja - g++ *.cpp -o app -lncurses

1. Konstrukcja funkcji pośredniczącej między backendem, a toolem - bind
backend->bind( (1)komenda, (2)funkcja, (3)instrukcja ) przykładowe wywołanie "backend->bind("#vim#:a<ENTER>", fun, "Help guidance instructions")"

(1)komenda - mogą być w stylu "vimowski" (np. ":a"), jedno znakowe (np. "a"), <CTRL> + litera (np. "<CTRL>W"), strzałki ("<UP>", "<DOWN>","<LEFT>","<RIGHT>"), backspace("<BACKSPACE>"), enter("<ENTER>") ... można dodać obsługę większej ilości jeśli będzie potrzeba.
UWAGA! Komenda <CTRL> nie działa z literami Q, S, J, Z, C, M


(2)funkcja - zakładam, że funkcję można podać tylko na dwa sposoby
- Bindowanie funkcji, albo metody statycznej
back -> bind(komenda, testFunc, instrukcje);

- Bindowanie metody nie statycznej -  w tym przypadku trzeba pamiętać o utworzeniu instancji klasy na której chcemy wywołać metodę
back -> bind(":c<ENTER>.some comment",[&]() mutable {front.testFunc();},"Instruction");

(3)instrukcja - tekst, który będzie wyświetlał się po uruchomieniu sekcji "help"

Przykładowe wywołania;
back -> bind("<EDITION>", [&]() mutable {front.editMode();}, "Edition mode"); <-- przypisanie funkcji odpowiedzialnej za tryb edycji
back -> bind("#vim#:a<ENTER>%some comment", [&]() mutable {front.testFunc1();},"instruction"); <-- po "%" albo "." można zamieścić komentarz
back -> bind("#vim#:a<ENTER>",[&]() mutable {front.testFunc1();},"instruction");
back -> bind("#nano#:ab",[&]() mutable {front.testFunc();},"instruction"); <-- ze względu na #nano# komenda ta nie będzie dodana
back -> bind(":c<ENTER>.some comment",[&]() mutable {front.testFunc();},"instruction");
back -> bind("<CTRL>A", &OneFrontend::methA, "Open a file ctrl R");
back -> bind("<ENTER>!EDIT", &OneFrontend::methA, "Open a file ctrl R"); <-- z "!EDIT" po wywołaniu funkcji OneFrontend::methA wejdziemy do trybu EDITION 

back -> bind("#vim#:open ${FILE_NAME}<ENTER>", &OneFrontend::methA, "Open a file from class"); <-- w przypadku gdy mamy komendę z parametrem (${FILE_NAME} <-- parametr ),na początku wywoła się funkcja toola "setEntry" z wartościami parametrów padanych podczas używania aplikacji (w tym przypadku dla wywołania :open "filename.txt", zostanie wywołana funkcja "tool->setEntry("FILE_NAME","filename.txt"), a następnie funkcja bindowana "&OneFrontend::methA")

2. Komenda żeby odpalić sekcję help - :h albo :help (przykładowa linia ":a<ENTER> - instruction")

3. Komneda żeby wyjść z backendu :q, :quit, ZZ. Przy wychodzeniu zostanie sprawdzona wartość toola "IS_SAVED" == "NO" (tool->getEntry("IS_SAVED") == "NO")). Jeśli zostanie zwrócona wartość "true" to użytkownik zostanie zapytany czy na pewno ma zamiar opóścić aplikację.

4. W trybie edycji wykonujemy w pętli operacje:
  - pobrania jednego znaku z klawiatury, który zostanie zapisany w sekcji "KEY" np. tool->aetEntry("KEY","A")
  - wywołania funkcji przypisanego jako tryb edycji przez tworzącego frontend
Wyjeście z trybu edycji nastąpi gdy użytkownik naciśnie "Escape".

5. Konieczne jest zbindowanie funkcji refreshRoutine (np. back -> setRefreshRoutine([&]() mutable {this -> refreshRoutine();});). Powinna to być funkcja która odświerza zawartość ekranu (backend przed jej wykonaniem zeruje wszystko co jest na ekranie - tutaj mogą być różne koncepcje dlatego w razie konfliktu można dokonać zmiany)
