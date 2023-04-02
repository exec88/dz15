# dz15
Реализована возможность регистрации пользователя в чате, также входа в чат по паролю с использованием хэш таблицы с закрытым хэшированием. 
При формировании хэш таблицы используется метод квадратичного пробирования. 
В классе Chat хранится объект хэш таблицы, в которой логины и соответствующие пароли хранятся в виде пар. 
Доступны метоты добавления новой пары логин-пароль, удаление пары, поиск пароля по логину. 
При регистрации пароль шифруется методом sha1.
