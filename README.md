![](https://img.shields.io/github/license/men100/MJScore)

# MJScore

This is a Mahjong score calculation library.<br>
If a pat is made from the entered values, the name of the role and its score are displayed.<br>

It is released under the MIT license, so please use it within the scope of your own responsibility.

# Rule

The default rule is the following.
If you change it, please call corresponding function.
(For the detail, please refer Function Description section)

- No red tiles
- Enable kuitan
- No round up mangan
- No basengo
- No double yakuman in kokushi-muso thirteen-sided wait
- No double yakuman in churen-poto nine-sided wait
- No double yakuman in daisushi
- No double yakuman in suanko one-side wait

# Data Description

## tehai

The tehai array indicates the hand of Mahjong.
The size of array is MJSCORE_INPUT_TEHAI_NUM (41).

- Only non-fuuro tiles are included.
- Agari tiles are also included.
- Unused tiles must be set to 0.

### tehai mapping

| Array index | Hand's type     |
| ----        | ----            |
| 0           | undefined       |
| 1 to 9      | 1 to 9 of Manzu |
| 10          | undefined       |
| 11 to 19    | 1 to 9 of Pinzu |
| 20          | undefined       |
| 21 to 29    | 1 to 9 of Sozu  |
| 30          | undefined       |
| 31          | East            |
| 32          | South           |
| 33          | West            |
| 34          | North           |
| 35          | Haku            |
| 36          | Hatsu           |
| 37          | Chun            |
| 38          | Red 5 of Manzu  |
| 39          | Red 5 of Pinzu  |
| 40          | Red 5 of Sozu   |

## fuuro

The fuuro array indicates the fuuro tiles.
The size of array is MJSCORE_INPUT_FUURO_NUM (20).

### fuuro mapping

| Array index | Description     |
| ----        | ----            |
| 0 + 4*n     | The type of fuuro (0 = no fuuro, 1 = pon, 2 = chi, 3 = ankan, 4 = minkan, 5 = kakan)
| 1 + 4*n     | The smallest tile number of its sets |
| 2 + 4*n     | The called tile number of its sets   |
| 3 + 4*n     | The type of the other called house that relative to that person (1 = lower house, 2 = facing, 3 = upper house) |

## dora

The dora array indicates the dora tiles.
The size of array is MJSCORE_INPUT_DORA_NUM (11).

### dora mapping

| Array index | Hand's type                        |
| ----        | ----                               |
| 0           | The number of dora display tiles   |
| 1 to 5      | 1st to 5th dora display tile       |
| 6 to 10     | 1st to 5th "ura" dora display tile |

# Function Description

## Rule related functions

### void Avail_Akahai(`bool arg`);

Enable or disable red tiles in rule

### void Avail_Kuitan(`bool arg`);

Enable or disable kuitan in rule

### void Avail_ManganKiriage(`bool arg`);

Enable or disable round up mangan in rule

### void Avail_Ba1500(`bool arg`);

Enable or disable basengo in rule

### void Avail_DoubleKokushi13(`bool arg`);

Enable or disable double yakuman in kokushi-muso thirteen-sided wait in rule

### void Avail_DoubleTyuuren9(`bool arg`);

Enable or disable double yakuman in churen-poto nine-sided wait in rule

### void Avail_DoubleDaisuusii(`bool arg`);

Enable or disable double yakuman in daisushi in rule

###	void Avail_DoubleSuttan(`bool arg`);

Enable or disable double yakuman in suanko one-side wait in rule

## Input related functions

###	void Set_Tehai(`int t[]`);

Input tehai

###	void Set_Fuuro(`int f[]`);

Input fuuro

###	void Set_Dora(`int d[]`);

Input dora

### void Set_Jikaze(`int arg`);

Input jikaze

### void Set_Bakaze(`int arg`);

Input bakaze

### void Set_Agarihai(`int arg`);

Input winning tile

###	void Set_Tumoagari(`int arg`);

Input whether tumo or not.
True is tumo, false is ron.

### void Set_Honba(`int arg`);

Input how many places

###	void Set_KyoutakuRIichi(`int arg`);

Input whether deposition reach or not

### void Set_Dorasuu(`int arg`);

Input the number of dora

### void Is_Riichi(`bool arg`);

Input whetehr riichi or not

### void Is_Tenhou(`bool arg`);

Input whether tenho or not

###	void Is_Tiihou(`bool arg`);

Input whether tiho or not

###	void Is_DoubleRiichi(`bool arg`);

Input whether double richi or not

###	void Is_Ippatu(`bool arg`);

Input whether ippatu or not

###	void Is_Tyankan(`bool arg`);

Input whether tyankan or not

### void Is_Rinsyan(`bool arg`);

Input whether rinsyankaiho or not

###	void Is_NagashiMangan(`bool arg`);

Input whether nagashimangan or not

### void Is_Haitei(`bool arg`);

Input whether haitei or not

## Run Function

### void Run();

Perform calculation

## Output related functions

### int Get_ErrorCode();

Get error code.

| Error Code | Desription    |
| ----       | ----          |
| -1         | uncalculating |
| 0          | success       |
| 1          | invalid input data (non furo tiles + the number fuuro * 3 isn't 14 or the elements of tehai have less than 0 or greater than 5) |
| 2          | invalid input data (No information on winning tile or no winning tile in hand) |
| 3          | invalid input data (no finished) |
| 4          | invalid input data (no information of bakaze or jikaze) |
| 5          | invlaid input data (called and reached) |
| 6          | no tile combination |

### int Get_OyaRon();

Get score in case of Parent's ron

### int Get_OyaTumo();

Get score in case of Parent's tumo

###	int Get_KoRon();

Get score in case of Child's ron

###	int Get_KoTumoOya();

Get score in case of Child's tumo to Parent

###	int Get_KoTumoKo();

Get score in case of Child's tumo to other child

### int Get_Fu();

Get fu nunber

### int Get_Fan();

Get fan number

###	int Get_TokutenOya();

Get final score the parent receives in case of ron

###	int Get_TokutenKo();

Get final score the child receives in case of ron

###	int Get_TokutenOyaTumo();

Get final score the parent receives in case of tumo

###	int Get_TokutenKoTumo();

Get final score the child receives in case of tumo

### void Get_Yakutable(`bool t[]`);

Get yaku table array.
The size of array is 60.

###	void Get_Yakuname(`string []`);

Get yaku name array.
The size of array is 20.

###	int Get_Dorasuu();

Get the number of dora

### int Get_Uradorasuu();

Get the number of "ura" dora

### int Get_Akadorasuu();

Get the number of akadora

### bool Get_Ismangan();

Get whether mangan or not

### void Get_ResultKiriwake(`int *arg`);

Get each sets after evaluation

## Other functions

### void Clear();

Clear the state

###	void Clear_WithoutRule();

Clear the state without rule

# Special Thanks

This library is based on the following source code. Thanks to cmj3-san!<br>
http://cmj3.web.fc2.com/index.htm#mjscore
