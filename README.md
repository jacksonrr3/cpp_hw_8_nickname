# cpp_hw_8_nickname

nickname
Условие
Пользуясь имеющимися в библиотеке STL структурами и алгоритмами разработать новую структуру Radix
Tree и операции над ней.
Пользуясь полученной структурой определить минимальное количество символов достаточных для
однозначного определения пользователя по его имени, предварительного добавленных в новый контейнер
из стандартного ввода.
Например, для имен Данил, Денис и Даша мы хотим получить
Данил - Дан
Денис - Де
Даша - Даш
Radix Tree
Пример структуры узла:
class RadixTrie {
struct Node {
std::string label;
bool is_end{};
std::array<std::unique_ptr<Node>, 26> children;
};
std::unique_ptr<Node> root;
public:
static void append(std::unique_ptr<Node> &node, const std::string &label) {
// TODO
}
void append(const std::string &label) {
append(root, label);
}
};
Ссылки для понимания работы структуры:
• Визуалиазация RadixTree
• https://en.wikipedia.org/wiki/Radix_tree
Пример
Символ $ обозначает признак завершения строки. Текст выводится в кавычках для обозначения границ
текста.
Добавление "aleksey".
"aleksey"$
Добавление "sasha". Корень становится пустой строкой без признака завершения.
""
├ "aleksey"$
└ "sasha"$
Добавление "aleks"
""
├ "aleks"$
│ └ "ey"$
└ "sasha"$
Добавление "alek"
1
