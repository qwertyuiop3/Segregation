# Ветки
[Counter-Strike: Source](https://github.com/qwertyuiop3/Segregation/tree/css_nosteam) (версия 34)  
[Counter-Strike: Source](https://github.com/qwertyuiop3/Segregation/tree/css_steam) (версия последняя)  
[Garry's Mod](https://github.com/qwertyuiop3/Segregation/tree/gmod_x64) (версия x86_64. [@m4tt13](https://github.com/m4tt13))  
[Counter-Strike: Global Offensive](https://github.com/qwertyuiop3/Segregation/tree/csgo_2018) (версия 2018)
# Сборка и запуск
1. Установить зависимости: `Visual Studio, Clang, WDK` (все в одном [установщике](https://visualstudio.microsoft.com/downloads/)).  
2. Открыть `Segregation.vcxproj` через `Visual Studio`.  
3. Отключить "Расширенный набор инструкций" в настройках проекта, если оные не поддерживаются.
4. Запустить сборку комбинацией Ctrl+Shift+B.  
5. Запустить игру, открыть `Segregation.cpl`.
# Предварительная конфигурация (в процессе коррекции)
Чтобы выровнять, насколько то возможно, снимок данных (углы, координаты, анимационные циклы) цели во время компенсаторики RTT в [интерполяционной доле](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_lagcompensation.cpp#L471-L473), что высчитывается при негативном расхождении между серверным и клиентским штампом времени обновления, и минимизировать сдвиг (ограниченный в ~200ms, если не учитывать `sv_maxunlag` - ответственный за [компенсацию RTT](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_lagcompensation.cpp#L335-L359)) от последнего штампа, тем самым продлевая окно попадания: `cl_updaterate N;cl_interp_ratio 0;cl_interp 0;host_writeconfig`, где `N` подразумевает частоту симуляции конкретного сервера.  

Так как сервер отправляет лишь последний снимок данных симуляции, а интерполяция строится из промежуточных данных, которые клиент упускает, как правило, то цель - уменьшить интерполяционную долю, насколько это возможно, что говоря боковым зрением - является основопологающей в нагромождении эффективностей искусственной задержки.  

Для условных конфигураций: утилизируется [внутриигровая система](https://developer.valvesoftware.com/wiki/CFG) програмированния (`alias`, `bind`) и исполнения программных файлов (`exec`). Например, переключение конфигурации между состоянием прыжка:
```
alias +conditional_jump "exec jump_condition;+jump"
alias -conditional_jump "exec unjump_condition;-jump"
bind space +conditional_jump
```
# Игровая конфигурация (в процессе коррекции)
|Переменная|Описание|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Рабочий диапазон &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|
|:-:|:-:|:-:|
|`Commentator`|Воспроизведение событийного звука `player_death` ("Ленин в Октябре" 1937-го).<br>Самоубийство не учитывается.|[0, 1]|
|`Bruteforce_Memory_Tolerance`|Допустимое количество промахов по креплению `m_flGoalFeetYaw`, восстанавливается через `player_death`, индивидуально аннулируется в локальном `player_death`.|[0, 2147483647]|
|`Bruteforce_Tolerance`|Повыстрельный интервал между итерациями "грубой силы", восстанавливается через `player_hurt`.|[0, 2147483647]|
|`Bruteforce`|Повыстрельное нахождение (коллидирующего) `m_flGoalFeetYaw` методом "грубой силы".<br>Выстрел устанавливает последующие терпимостей и целевого `m_flGoalFeetYaw`, после чего переходит в режим ожидания события.<br>По пришествию `player_hurt` либо `player_death`, по состоянию попадания в целевой параллелепипед: закрепляется `m_flGoalFeetYaw` и восстанавливаются терпимости.<br>По пришествию `bullet_impact` в течении ~500ms, выстрел классифицируется зарегистрированным, в противном случае подборочный снимок данных откатывается до предвыстрельного.|[0, 1]|
|`Bruteforce_Angles`|Набор целевых `m_flGoalFeetYaw`, заменяющих собой эталонные вычисления.|[-180.0, 180.0][127]|
|`Target_On_Simulation`|Требование к ожиданию обновления `m_flSimulationTime` перед выстрелом, - в придачу сломления [условия телепортации](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_lagcompensation.cpp#L431-L436).<br>В первом случае возможно искажение [относительных операций](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/client/c_baseentity.cpp#L362-L368); во втором же возможнен ложноотрицательный либо ложноположительный результат по причине отсутствия истинных промежуточных.|[0, 2]|
|`Alternative`|В обыкновенном режиме: выстрел происходит моментом до обрыва искусственной задержки, порядок которой фиксируется резервацией предыдущих данных.<br>В альтернативном режиме: выстрел обрывает искусственную задержку, включительно до последующей симуляции, тем самым раскрывая промежуточные, однако же, анимационный массив [`m_flPoseParameter`](https://developer.valvesoftware.com/wiki/Player_Models) не составляет [часть](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_lagcompensation.cpp#L84-L98) компенсаторики RTT.|[0, 1]|
|`Duck_Advantage`|Имитация движения с прожатием `+duck`, в случае подтверждённого преимущества горизонтальной скорости - реализация.|[0.0, 3.4028235e38 - Speed]|
|`Minimum_Choked_Commands`|Минимум задушенных промежуточных.<br>Начиная с натуральных чисел, возможна мистификация: `m_fFlags`, `m_vecOrigin`, `m_vecVelocity`, `m_vecAngles`, `m_flGoalFeetYaw`; и запоздалость анимационных циклов вслед за [сбросом](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/sdk/sdk_playeranimstate.cpp#L519-L534).|[0, 21]|
|`Maximum_Choked_Commands`|Максимум задушенных промежуточных.<br>Обрывается по достижению [условия телепортации](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_lagcompensation.cpp#L431-L436), необходимого для прерывания компенсаторики RTT.|[0, 21]|
|`Aim_Intersection`|Разрешение прицеливания в пересечение целевого параллелепипеда.<br>Урон будет причинён, но суммирования `CTakeDamageInfo` параллелепипедов - не будет.|[0, 1]|
|`Aim_Height`|Приближение от наинижайшей вершины параллелепипеда до наивысшей.<br>В случае наклонного параллелепипеда, точка наводки - центр - может выходить за границы оного.|[0.0, 1.0]|
|`Angle_X`|Угол вертикального наклона головы.<br>Ограничивается диапазоном [-90.0, 90.0] в серверном [`FinishMove`](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/server/player_command.cpp#L208-L222), но искажается перед этим нормализацией клиентской интерполяции.<br>Компрессия чисел на `Windows` отличается, тем самым искажая значение с `180.0` до `180.08794` при получении клиентом.|[-180.0, 180.0]|
|`First_Choked_Angle_Y`|Первый задушенный угол горизонтального вращения тела относительно цели.<br>Последующая движимая разница ограничивается диапазоном [`m_flMaxBodyYawDegrees`](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/sdk/sdk_playeranimstate.cpp#L146); недвижимая же разница лишённая [обновлений](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/base_playeranimstate.cpp#L816-L817) по `m_flEyeYaw` ограничивается аккумулятивной способностью [`ConvergeAngles`](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/base_playeranimstate.cpp#L775-L785) вплоть до рабочего диапазона.|[-180.0, 180.0]|
|`Second_Choked_Angle_Y`|Второй задушенный угол горизонтального вращения тела относительно цели.<br>Используется для поддержания разницы ([`m_flLastTurnTime`](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/base_playeranimstate.cpp#L833-L837)) во время душения.|[-180.0, 180.0]|
|`Angle_Y`|Передаваемый угол горизонтального вращения тела относительно цели, используемый клиентом для [вычисления](https://github.com/rom4s/hl2sdk-ep1c/blob/game-cstrike-1/game/shared/base_playeranimstate.cpp#L854-L860) `m_flGoalFeetYaw`.<br>Визуализировать десинхронизацию можно через `thirdperson;sv_showhitboxes I`, где `I` подразумевает собственный индекс, либо `sv_showanimstate I`, где `body_yaw` исчисляет отклонение.|[-180.0, 180.0]|
|`Uber_Alles_Scale`|Отображаемая величина символического верховенства, заменяющего собой внутриигровой прицел.|[0, min(Width, Height) / 2 - 1]|
|`Uber_Alles_Speed`|Скорость развёртывания символического верховенства, по сути - прибавочный угол по истечению секунды.|[0, 360 * FPS]|

|Команда|Описание|Порядок|
|:-:|:-:|:-:|
|`Get_Priorities`|Запрашивает сверочно-сопоставительную таблицу, содержащую идентификаторы для последующей установки либо определения настоящего приоритета.|`Клиент`<br>`Индекс`<br>`Приоритет`|
|`Set_Priority`|Устанавливает конкурентный приоритет при взятии цели, чем значение меньше, тем вторичнее, и наоборот больше - первичнее.<br>Специальные значения:<br>* -2 ("чистый" список; игнорируется "грубой силой"; считывается как нулевой);<br>* -1 ("белый" список; исключает индекс из целевого формирования).|`Индекс`<br>[1, 64]<br>`Приоритет`<br>[-127, 127]|