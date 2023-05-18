Данный код реализует поиск автодополнений для введенного пользователем префикса слова с использованием Trie (префиксного дерева).
Программа строит Trie из заданного словаря, используя функцию insert(). 
Затем, при каждом цикле, программа запрашивает у пользователя часть слова и находит все слова из словаря, которые начинаются с этой части, используя функцию findAutocomplete(). 
Функция findAutocomplete() обходит дочерние узлы Trie, начиная с узла, соответствующего последней букве префикса, и добавляет вектору result все слова, которые можно получить, дописав к префиксу символы из дочерних узлов.
