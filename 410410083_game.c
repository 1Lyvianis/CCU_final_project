//main function is at 75th row
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
struct player_information{
    int health;
    int strength;
    int role;
    int level;
    int exp;
    int passive_ability;
    char name[11];
    int x;
    int y;
    bool gameover;
};
struct map_information{
    int row;
    int col;
    char **arr;
};
struct monster_information{
    int health;
    int strength;
    int level;
    char name[100];
    bool dead;
};
struct battle_information{
    int player_health;
    int monster_health;
    int player_strength;
};
typedef struct player_information info;
typedef struct map_information info2;
typedef struct monster_information info3;
typedef struct battle_information info4;
    void select_role(info * player);
    void name(info * player);
    void create_map(info2 * map);
    bool are_you_sure();
    void settings_before_game(info * player);
    void check_level_up(info * player);
    void settle(info * player);
    void print_map(info player, info2 * map);
    bool check_occupied(info2 * map, int tempx, int tempy);
    void set_up_map_objects(info * player, info2 * map);
    bool check_boundary(int tempx, int tempy, info player, info2 map);
    void go_up(info * player, info2 * map);
    void go_down(info * player, info2 * map);
    void go_left(info * player, info2 * map);
    void go_right(info * player, info2 * map);
    void movement(info * player, info2 * map);
    void trap(info * player);
    void gun(info * player);
    void village(info *player);
    info3 generate_monster(info player);
    void berserker(info * player, int health);
    void player_attack(info * player, info3 * monster, info4 initial);
    void monster_attack(info * player, info3 * monster, info4 initial);
    void battle(info * player);
    info3 generate_boss();
    void boss_attack(info * player, info3 * boss, info4 initial);
    void player_attack_boss(info * player, info3 * boss, info4 initial);
    void battle_boss(info * player);
    void game_introduction();
    void overall_introduction();
    void check_object(info * player, info2 * map, int tempx, int tempy);
    bool check_level(info player, info3 boss);
    bool dodge();
    void adventure(info * player, info2 * map);
int main()
{
    system("cls");
    //seed set
    srand((unsigned)time(NULL));
    info player;
    info2 map;
    adventure(&player, &map);
    return 0;
}
/////////////////////////////////////////////end of main
void select_role(info *player)
{
    printf("請選擇您的職業~ 依數字鍵查看職業介紹:\n");
    while(1){
        printf("1.\033[43;30;5m狂戰士\033[0m 2.\033[43;31;5m吸血鬼\033[0m 3.\033[43;32;5m'資'識份子\033[0m : ");
        int option;
        scanf("%d", &option);
        printf("\n");
        switch(option){
            case 1:
                printf("\033[43;30;5m狂戰士<赫拉克勒斯>\033[0m : 希臘神話中半人半神的英雄。因其出身而受到宙斯的妻子赫拉的強烈憎惡，每有機會就會受到女神折磨\n。");
                printf("然而，他跨越所有給予他的苦難，最後以一尊神的身份受到祭祀。\n");
                printf("被動技能 : \033[43;30;5m<戰鬥續行‧ 雪之城>\033[0m\n");
                printf("守護心愛之人的意志使你屹立不搖。赫拉克勒斯在瀕死時進入狂暴狀態，");
                printf("當赫拉克勒斯的血量降至零點以下，將發動此效果，恢復戰鬥開始前的血量，並以雙倍攻擊力戰鬥。\n");
                printf("然而，戰鬥結束後，赫拉克勒斯的血量將降至一點，且攻擊力回歸正常。\n");
                printf("注意 : 此技能在整場遊戲中指能觸發三次。\n");
                printf("再次注意 : 採到陷阱致死(蠢死)無法觸發此技能!\n");
                if(are_you_sure())
                {
                    player->role = 1;
                    player->passive_ability = 3;
                    return;
                }
                break;
            case 2:
                printf("\033[43;31;5m吸血鬼<弗拉迪米爾>\033[0m : 弗拉迪米爾是一名渴望著人類鮮血的惡魔。除了可以透過不尋常的方式延長他的生命，\n");
                printf("他對於鮮血的掌握也使他可以輕易地操控他人的心智與身體 － 如同他操控自己一樣簡單。\n");
                printf("被動技能 : \033[43;31;5m<血色契約>\033[0m\n");
                printf("舔血維生的弗拉迪米爾在戰鬥勝利時，可以抽乾對方肉體所殘留的血液直至乾涸。\n");
                printf("每當弗拉迪米爾擊敗對手，將獲得對方初始生命*0.5倍的血量\n");
                if(are_you_sure())
                {
                    player->role = 2;
                    player->passive_ability = 1;
                    return;
                }
                break;
            case 3:
                printf("\033[43;32;5m'資'識份子<helloworld>\033[0m : 資工系，美其名為資訊工程系，實為一群穿著人皮的猴子，\n");
                printf("並以身為工具人為傲。故應正名「吱吱工具系」。\n");
                printf("被動技能 : \033[43;32;5m<駭客視野>\033[0m\n");
                printf("吱工系的學生對於資訊的取得、處理相當傑出，常能以更有效率的手段取得自己想要的資訊。\n");
                printf("因此，helloworld不受戰爭迷霧的影響，可以直接看見地圖全局。\n");
                printf("槍枝 : \033[35;5m'g'\033[0m ; 陷阱 : \033[33;5m't'\033[0m ; 村莊 \033[32;5m'v'\033[0m ; 虛擬主播 \033[31;5m'm'\033[0m \n");
                if (are_you_sure())
                {
                    player->role = 3;
                    player->passive_ability = 1;
                    return;
                }
                break;
            default:
                system("cls");
                printf("我的腦子好像有洞，並沒有這個選項。\n");
                continue;
        }
    }
}
void name(info *player)
{
    printf("\033[34;1m(羅馬尼‧ 阿基曼)\033[0m : \033[46;37;5m決戰用兵器代號000\033[0m...不，是時候幫你取一個正常點的名子了!\n");
    printf("不過，名子取太長的話，唸起來也不太方便呢~\n\n");
    char arr[100000];
    while(1)
    {
        printf("提示 : 請輸入\033[32;5m10個字元以內的英數字\033[0m : ");
        scanf("%s", arr);
        if(strlen(arr) > 10)
        {
            system("cls");
            printf("我的腦子好像有洞，並沒有這個選項。\n");
        }
        else
            break;
    }
    strcpy(player->name,arr);
    system("cls");
    printf("\033[34;1m(羅馬尼‧ 阿基曼)\033[0m : 我想到啦! 就叫做 \033[46;37;5m %s \033[0m 如何? 真是個好名子呢~\n", arr);
    printf("-------------------------------------------\n");
}
void create_map(info2 *map)
{
    printf("玩家您好，謝謝您選擇這款遊戲!\n在開始遊玩之前，請先輸入地圖大小\n");
    while(1){
        printf("提示 : 地圖的\033[32;5m長、寬皆為5以上，1000以內的整數\033[0m。輸入格式:\033[32;5m(長)(space)(寬)(enter)\033[0m\n");
        scanf("%d %d",&map->row,&map->col);
        if(map->row >1000 || map->col >1000 || map->row<5 || map->col <5){
            system("cls");
            printf("我的腦子好像有洞，並沒有這個選項。\n");
        }
        else {
            system("cls");
            printf("遊戲將以\033[32;5m%d乘%d\033[0m的地圖進行, 接著進入角色設定環節。\n",map->row,map->col);
            printf("-------------------------------------------\n");
            break;
        }
    }
    map->arr = (char **)malloc(sizeof(char *) * map->row);
    for (int i = 0; i < map->row;i++)
    {
        map->arr[i] = (char *)malloc(sizeof(char) * map->col);
        //memset(map->arr[i], '.', sizeof(map->arr)+1);
    }
    for (int i = 0; i < map->row;i++)
    {
        for (int j = 0; j < map->col;j++)
        {
            map->arr[i][j] = '.';
        }
    }
}
bool are_you_sure()
{
    Sleep(2);
    printf("-------------------------------------------\n");
    printf("那你要確定餒 ! 等下就不能改囉 ?\n");
    int flag;
    while(1)
    {
        printf("1 : 廢話少說，老子就要這個  0 : 對不起，請讓我重選 :");
        scanf("%d", &flag);
        switch(flag){
            case 1:
                return 1;
            case 0:
                system("cls");
                return 0;
            default:
                system("cls");
                printf("我的腦子好像有洞，並沒有這個選項。\n");
        }
    }
}
void settings_before_game(info *player)
{
    name(player);//name
    select_role(player);//role
    player->exp = 0;
    player->level = 1;
    player->health = 10;
    player->strength = 1;
    player->gameover = 0;
    system("cls");
    printf("你的名子是 : \033[46;37;5m%s\033[0m   ", player->name);
    switch(player->role){
        case 1:
            printf("你是一名\033[43;30;5m 狂戰士\033[0m\n");
            break;
        case 2:
            printf("你是一名\033[43;31;5m 吸血鬼\033[0m\n");
            break;
        case 3:
            printf("你是一名\033[43;32;5m '資'識份子\033[0m\n");
            break;
    }
    settle(player);
    printf("\033[42;5m~~~~~~即將開始拯救人理~~~~~~\033[0m\n");
    system("pause");
    system("cls");
}
void check_level_up(info *player)
{
    while(player->exp >= player->level)
    {
        player->exp -= player->level;
        ++player->level;
        player->health += 2;
        player->strength += 1;
    }
    if(player->level != 1)
    {
        printf("恭喜~您已升級!等級提升至%d等!\n", player->level);
        printf("生命恢復了2點，攻擊力上升了1點!\n");
    }
}
void settle(info *player)
{
    check_level_up(player);
    printf("你目前擁有~~\n");
    printf("血量 : %d ", player->health);
    printf("攻擊力 : %d\n", player->strength);
    printf("等級 : %d ", player->level);
    printf("距離升級還差經驗值 : %d點\n", player->level - player->exp);
    if(player->role == 1){
        if(player->passive_ability > 0)
        {
            printf("狂戰的血脈在你體內沸騰。你還有%d次戰鬥續行的機會\n", player->passive_ability);
        }
        else
        {
            printf("你已經沒有戰鬥續行的機會\n");
        }
    }
}
void print_map(info player,info2 *map)
{
    if(player.role == 3)
    {
        for (int i = 0; i < map->row;i++)
        {
            for (int j = 0; j < map->col;j++)
            {
                switch(map->arr[i][j]){
                    case '.':
                        printf(" %c ", map->arr[i][j]);
                        break;
                    case 'm':
                        printf("\033[31;5m m \033[0m");
                        break;
                    case 'v':
                        printf("\033[32;5m v \033[0m");
                        break;
                    case 'p':
                        printf("\033[46;37;5m P \033[0m");
                        break;
                    case 'g':
                        printf("\033[35;5m g \033[0m");
                        break;
                    case 't':
                    printf("\033[33;5m t \033[0m");
                    break;
                case 'b':
                    printf("\033[41;36;5m B \033[0m");
                }
            }
            printf("\n");
        }
    }
    else
    {
        for (int i = 0; i < map->row;i++)
        {
            for (int j = 0; j < map->col;j++)
            {
                switch(map->arr[i][j]){
                    case '.':
                        printf(" %c ", map->arr[i][j]);
                        break;
                    case 'm':
                        printf(" x ");
                        break;
                    case 'v':
                        printf(" x ");
                        break;
                    case 'p':
                        printf("\033[46;37;5m P \033[0m");
                        break;
                    case 'g':
                        printf(" x ");
                        break;
                    case 't':
                        printf(" x ");
                        break;
                    case 'b':
                        printf("\033[41;36;5m B \033[0m");
                }
            }
            printf("\n");
        }
    }
}
bool check_occupied(info2 *map,int tempx,int tempy)
{
    if(map->arr[tempx][tempy] != '.')
    {
        return 1;
    }
    else
        return 0;
}
void set_up_map_objects(info *player,info2 *map)
{
    int tempx, tempy,cnt = 0;
    int village_num = (map->row + map->col)/5, monster_num = (map->row + map->col)/2;
    int trap_num = (map->row + map->col) / 4, gun_num = (map->row + map->col) / 3;
    while(cnt != village_num+1)
    {
        tempx = rand() % map->row;
        tempy = rand() % map->col;
        if(!check_occupied(map,tempx,tempy))
        {
            map->arr[tempx][tempy] = 'v';
            cnt++;
        }
    }
    player->x = tempx;
    player->y = tempy;
    map->arr[tempx][tempy] = 'p';
    cnt = 0;
    while(cnt != monster_num)
    {
        tempx = rand() % map->row;
        tempy = rand() % map->col;
        if(!check_occupied(map,tempx,tempy))
        {
            map->arr[tempx][tempy] = 'm';
            cnt++;
        }
    }
    cnt = 0;
    while(cnt != trap_num)
    {
        tempx = rand() % map->row;
        tempy = rand() % map->col;
        if(!check_occupied(map,tempx,tempy))
        {
            map->arr[tempx][tempy] = 't';
            cnt++;
        }
    }
    cnt = 0;
    while(cnt != gun_num)
    {
        tempx = rand() % map->row;
        tempy = rand() % map->col;
        if(!check_occupied(map,tempx,tempy))
        {
            map->arr[tempx][tempy] = 'g';
            cnt++;
        }
    }
    while(check_occupied(map,tempx,tempy))
    {
        tempx = rand() % map->row;
        tempy = rand() % map->col;
    }
    map->arr[tempx][tempy] = 'b';
}
bool check_boundary(int tempx,int tempy,info player,info2 map)
{
    if(tempx <0 || tempx == map.row || tempy < 0 || tempy == map.col)
    {
        system("cls");
        printf("我不能往這裡移動。\n");
        print_map(player,&map);
        return 0;
    }
    else
        return 1;
}
void go_up(info *player, info2 *map)
{
    check_object(player, map, player->x - 1, player->y);
    player->x -= 1;
    if(map->arr[player->x][player->y] == 'b' && player->level < 4)
    {
        player->x += 1;
        return;
    }
    map->arr[player->x][player->y] = 'p';
    map->arr[player->x+1][player->y] = '.';
}
void go_down(info *player, info2 *map)
{
    check_object(player, map, player->x + 1, player->y);
    player->x += 1;
    if(map->arr[player->x][player->y] == 'b' && player->level < 4)
    {
        player->x -= 1;
        return;
    }
    map->arr[player->x][player->y] = 'p';
    map->arr[player->x-1][player->y] = '.';
}
void go_left(info *player, info2 *map)
{
    check_object(player, map, player->x, player->y-1);
    player->y -= 1;
    if(map->arr[player->x][player->y] == 'b' && player->level < 4)
    {
        player->y += 1;
        return;
    }
    map->arr[player->x][player->y] = 'p';
    map->arr[player->x][player->y+1] = '.';
}
void go_right(info *player, info2 *map)
{
    check_object(player, map, player->x, player->y+1);
    player->y += 1;
    if(map->arr[player->x][player->y] == 'b' && player->level < 4)
    {
        player->y -= 1;
        return;
    }
    map->arr[player->x][player->y] = 'p';
    map->arr[player->x][player->y-1] = '.';
}
void movement(info *player, info2 *map)
{
    printf("接著往哪走? 1.向上 2.向下 3.向左 4.向右\n");
    int option;
    scanf("%d", &option);
    system("cls");
    switch(option){
        case 1://up
            if(check_boundary(player->x-1, player->y,*player, *map))
            {
                go_up(player, map);
                if(player->gameover)
                    return;
                print_map(*player,map);
            }
            else
            {
                movement(player, map);
            }
            break;
        case 2://down
            if(check_boundary(player->x+1, player->y,*player ,*map))
            {
                go_down(player, map);
                if(player->gameover)
                    return;
                print_map(*player,map);
            }
            else
            {
                movement(player, map);
            }
            break;
        case 3://left
            if(check_boundary(player->x, player->y-1,*player, *map))
            {
                go_left(player, map);
                if(player->gameover)
                    return;
                print_map(*player,map);
            }
            else
            {
                movement(player, map);
            }
            break;
        case 4://right
            if(check_boundary(player->x, player->y+1,*player, *map))
            {
                go_right(player, map);
                if(player->gameover)
                    return;
                print_map(*player,map);
            }
            else
            {
                movement(player, map);
            }
            break;
        default:
            printf("我的腦子好像有洞，並沒有這個選項。\n");
            print_map(*player,map);
            movement(player, map);
    }
}
void trap(info *player)
{
    int damage = rand() % 3 + 1;
    player->health -= damage;
    if(player->health <= 0)
    {
        printf("都看看是誰踩到陷阱啦?\n");
        Sleep(2000);
        printf("風蕭蕭兮易水寒，壯士一去兮不復返。\n");
        Sleep(2000);
        printf("世界最後的希望 %s 最終採到陷阱，被自己蠢死\n", player->name);
        Sleep(2000);
        printf("遊戲結束，世界終將被虛擬主播統治。");
        Sleep(2000);
        player->gameover = 1;
    }
    else
    {
        printf("都看看是誰踩到陷阱啦? 你受到%d點傷害，剩下%d點血量，%d點攻擊力。\n", damage, player->health,player->strength);
    }
}
void gun(info *player)
{
    int aux = rand() % 2 + 1;
    player->strength += aux;
    printf("撿到了一把好槍! 你真是天選之人! 你增加%d點力量，現有%d點血量，%d點攻擊力\n", aux, player->health ,player->strength);
}
void village(info *player)
{
    int option,test=0;//test if already bought a sword in current visit
        printf("恭喜您!遇到了一個村莊!\n");
        Sleep(2000);
	while(1)//do until return(line 105), which is equivalent to existing a function
	{
        printf("你想在這個村莊內做些甚麼? (1:附魔; 2: 生命溫泉; 3:離開村莊?) : ");
        scanf("%d", &option); //input user's choice
        switch (option)
        {
		case 1://wanna buy a sword
			if(test==1)//already bought a sword
			{
                system("cls");
                printf("等一等，不可以貪貪。\n");
                Sleep(2000);
                printf("一個村莊只能附魔一次噢!\n");
                Sleep(2000);
            }
			else//not yet bought a sword
			{
                system("cls");
				player->strength+=1;
				printf("你感受到魔力在你身上流動!你得到了 1 點攻擊力!\n現在你共有 %d 點攻擊力!\n",player->strength);
                Sleep(2000);
				test=1;//flag that the user already bought a sword
			}
			break;
		case 2://health regen
			if(player->health>=10)
			{
                system("cls");
				printf("你的生命值不小於 10 點，生命溫泉無法起作用!\n");
                Sleep(2000);
			}
			else
			{
                system("cls");
				player->health=10;
				printf("你感受到活力在你身上流動! 你的生命已恢復至 10 點!\n");
                Sleep(2000);
			}
			break;
		case 3://leaving the village
            system("cls");
			printf("再會了，勇者!記住，你是我們最後的希望。\n");
            Sleep(2000);
            printf("隨著一陣強光，這個村莊被吸入二次元空間，就此消失了。\n");
            Sleep(2000);
            return;
		default://invalid input
            system("cls");
			printf("我的腦子可能有洞!沒有這個選項! (1:附魔; 2: 生命溫泉; 3:離開村莊) : ");
			break;
		}
	}
}
info3 generate_monster(info player)
{
    srand((unsigned)time(NULL));
    info3 monster;
    if(player.level <= 2)
    {
        monster.level = rand() % 2 + 1;
        monster.health = 2 + monster.level;
        monster.strength = 1 + monster.level;
    }
    else
    {
        monster.level = rand() % 3 + 3;
        monster.health = 4 + monster.level;
        monster.strength = 2 + monster.level;
    }
    monster.dead = 0;

    switch(monster.level){
        case 1:
            strcpy(monster.name, "死神");
            break;
        case 2:
            strcpy(monster.name, "鳳凰");
            break;
        case 3:
            strcpy(monster.name, "偵探");
            break;
        case 4:
            strcpy(monster.name, "鯊魚");
            break;
        case 5:
            strcpy(monster.name, "章魚");
            break;
    }
    return monster;
}
void berserker(info *player,int health)
{
    system("cls");
    printf("\033[41;36;5m \"我浴血而戰!!!\" \033[0m\n");
    //printf("\"我浴血而戰!!!\"\n");
    player->passive_ability -= 1;
    player->health = health;
    player->strength *= 2;
    printf("你的血量已歸零。\n");
    Sleep(2000);
    printf("技能觸發  \033[43;30;5m<戰鬥續行‧ 雪之城>\033[0m: 你進入狂暴狀態，擁有%d點血量和%d點攻擊力\n", player->health,player->strength);
    printf("即將重返戰場~~\n");
    system("pause");
}
void player_attack(info *player, info3 *monster,info4 initial)
{
            monster->health -= player->strength;
            if(monster->health <= 0)//win
            {
                printf("遭受%d點的攻擊後, 虛擬主播 \033[47;31;5m%s\033[0m 被擊敗了!\n",player->strength, monster->name);
                system("pause");
                system("cls");
                player->exp += monster->level;
                if(player->strength > initial.player_strength)//if berserkered
                {
                    printf("~~~狂暴結束，你進入虛弱狀態~~~\n");
                    player->health = 1;
                    player->strength = initial.player_strength;
                }
                if(player->role == 2)//if vladmir
                {
                    printf("~~~技能觸發  \033[43;30;5m<血色契約>\033[0m: 你抽取了%d點生命!~~~\n", initial.monster_health / 2);
                    player->health += initial.monster_health / 2;
                }
                printf("你得到了%d點經驗!\n", monster->level);
                settle(player);
                system("pause");
                system("cls");
                monster->dead = 1;
                return;
            }
            printf("遭受%d點的攻擊後, 虛擬主播 \033[47;31;5m%s\033[0m 還剩下%d點的血量\n",player->strength, monster->name, monster->health);
            Sleep(2000);
}
void monster_attack(info *player,info3 *monster,info4 initial){
        player->health -= monster->strength;
        if(player->health <= 0)//lose
        {
            if(player->role == 1 && player->passive_ability > 0)//if is berserker
            {
                berserker(player, initial.player_health);
                printf("狂暴中的\033[46;37;5m%s\033[0m獲得追加攻擊權!\n", player->name);
                player_attack(player, monster, initial);
            }
            else
            {
                printf("很遺憾，您的血量已歸零。\n");
                Sleep(2000);
                printf("風蕭蕭兮易水寒，壯士一去兮不復返。\n");
                Sleep(2000);
                printf("世界最後的希望 \033[46;37;5m%s\033[0m 最終被名為 \033[47;31;5m%s\033[0m 的虛擬主播擊敗了\n", player->name, monster->name);
                Sleep(2000);
                printf("遊戲結束，世界終將被虛擬主播統治。");
                player->gameover = 1;
                return;
            }
        }
        else{
            printf("遭受%d點的攻擊後, 玩家 \033[46;37;5m%s\033[0m 還剩下%d點的血量\n",monster->strength, player->name, player->health);
        }
}
void battle(info *player)
{
    info3 monster = generate_monster(*player);
    info4 initial;
    initial.player_health = player->health;
    initial.player_strength = player->strength;
    initial.monster_health = monster.health;
    printf("你的面前出現了一隻等級%d，名為 : \033[47;31;5m%s\033[0m 的虛擬主播! 它擁有%d點血量及%d點攻擊力。\n", monster.level, monster.name, monster.health, monster.strength);
    system("pause");
    while(1)
    {
        printf("~~~新回合開始~~~\n");
        printf("\033[46;37;5m%s\033[0m 對虛擬主播 \033[47;31;5m%s\033[0m 發動了攻擊!\n", player->name, monster.name);
        Sleep(2000);
        if(!dodge())
        {
            player_attack(player, &monster, initial);
            if(monster.dead)
            {
                return;
            }
        }
        else{
            printf("\033[46;37;5m%s\033[0m 的攻擊被閃避了!\n",player->name);
            Sleep(2000);
            printf("\033[47;31;5m%s\033[0m 展開了反擊!\n",monster.name);
            Sleep(2000);
            monster_attack(player, &monster, initial);
            if(player->gameover || monster.dead)
            {
                return;
            }
        }
        printf("虛擬主播 \033[47;31;5m%s\033[0m 對 \033[46;37;5m%s\033[0m 發動攻擊!\n", monster.name, player->name);
        Sleep(2000);
        if(!dodge())
        {
            monster_attack(player, &monster, initial);
            if(player->gameover || monster.dead)
            {
                return;
            }
            if(player->strength > initial.player_strength)
            {
                continue;
            }
        }
        else{
            printf("\033[47;31;5m%s\033[0m 的攻擊被閃避了!\n", monster.name);
            Sleep(2000);
            printf("\033[46;37;5m%s\033[0m 展開了反擊!\n", player->name);
            Sleep(2000);
            player_attack(player, &monster, initial);
            if(monster.dead)
            {
                return;
            }
        }
        printf("~~~回合結束~~~\n");
        system("pause");
    }
}
info3 generate_boss()
{
    info3 boss;
    boss.health = 20;
    boss.level = 6;
    strcpy(boss.name, "谷鄉元昭");
    boss.strength = 4;
    boss.dead = 0;
    return boss;
}
void boss_attack(info *player, info3 *boss,info4 initial){
        player->health -= boss->strength;
        if(player->health <= 0)//lose
        {
            if(player->role == 1 && player->passive_ability > 0)//if is berserker
            {
                berserker(player, initial.player_health);
                printf("狂暴中的\033[46;37;5m%s\033[0m獲得追加攻擊權!\n", player->name);
                player_attack(player, boss, initial);
            }
            else
            {
                printf("在虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 如暴雨般的攻勢下，你的生命值歸零了\n");
                Sleep(2000);
                printf("風蕭蕭兮易水寒，壯士一去兮不復返。\n");
                Sleep(2000);
                printf("世界最後的希望 \033[46;37;5m%s\033[0m 最終被名為 \033[41;36;5m谷鄉元昭\033[0m 的虛擬主播集團董事長擊敗了\n", player->name);
                Sleep(4000);
                printf("遊戲結束，世界終將被虛擬主播統治。");
                player->gameover = 1;
                return;
            }
        }
        else{
            printf("遭受%d點的攻擊後, 玩家 \033[46;37;5m%s\033[0m 還剩下%d點的血量\n",boss->strength, player->name, player->health);
        }
}
void player_attack_boss(info *player, info3 *boss,info4 initial){
    boss->health -= player->strength;
        if(boss->health <= 0)//win
        {
            printf("遭受%d點的攻擊後, 虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 被擊敗了!\n",player->strength);
            system("pause");
            system("cls");
            player->exp += boss->level;
            if(player->strength > initial.player_strength)//if berserkered
            {
                player->health = 1;
                player->strength = initial.player_strength;
            }
            if(player->role == 2)//if vladmir
            {
                printf("~~~技能觸發  \033[43;30;5m<血色契約>\033[0m: 你抽取了%d點生命!\n", initial.monster_health / 2);
                player->health += initial.monster_health / 2;
            }
            printf("你得到了%d點經驗!\n", boss->level);
            settle(player);
            system("pause");
            system("cls");
            printf("隨著最終boss的死亡，人類終於逃離虛擬主播的洗腦，回歸三次元的現實世界\n");
            Sleep(2000);
            printf("你成功\拯救了世界!\n");
            Sleep(2000);
            printf("___________________________________________________\n");
            printf("________00000000000___________000000000000_________\n");
            printf("______00000000_____00000___000000_____0000000______\n");
            printf("____0000000_____________000______________00000_____\n");
            printf("___0000000_______________0_________________0000____\n");
            printf("__000000____________________________________0000___\n");
            printf("__00000_____________________________________ 0000__\n");
            printf("_00000______________________________________00000__\n");
            printf("_00000_____________________________________000000__\n");
            printf("__000000_________________________________0000000___\n");
            printf("___0000000______________________________0000000____\n");
            printf("_____000000____________________________000000______\n");
            printf("_______000000________________________000000________\n");
            printf("__________00000_____________________0000___________\n");
            printf("_____________0000_________________0000_____________\n");
            printf("_______________0000_____________000________________\n");
            printf("_________________000_________000___________________\n");
            printf("____________________000_____00_____________________\n");
            printf("______________________00__00_______________________\n");
            printf("________________________00_________________________\n");
            printf("___________________________________________________\n");
            Sleep(2000);
            printf("由衷感謝您的遊玩!\n");
            system("pause");
            system("cls");
            for (int i = 5; i > 0;i--)
            {
                printf("遊戲將在%d秒後結束\n", i);
                Sleep(1000);
                system("cls");
            }
                boss->dead = 1;
            player->gameover = 1;
            return;
        }
        printf("遭受%d點的攻擊後,虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 還剩下%d點的血量\n", player->strength, boss->health);
}
void battle_boss(info *player)
{
    info3 boss = generate_boss();
    info4 initial;
    initial.player_health = player->health;
    initial.player_strength = player->strength;
    initial.monster_health = boss.health;
    int cnt = 0;
    printf("你的面前出現了一隻等級6，名為 : \033[41;36;5m谷鄉元昭\033[0m 的虛擬主播集團董事長! 它擁有20點血量及6點攻擊力。\n");
    system("pause");
    while(1)
    {
        if(check_level(*player,boss))
        {
            printf("你和虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 的層次差距過大，他的威壓令你無地自容。你像顆風中的塵土一般灰飛煙滅了\n");
            player->gameover = 1;
            return;
        }
        printf("~~新回合開始~~\n");
        printf("虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 對 \033[46;37;5m%s\033[0m 發動了攻擊!\n", player->name);
        Sleep(2000);
        if(!dodge())
        {
            boss_attack(player, &boss, initial);
            if(player->gameover || boss.dead)
            {
                return;
            }
        }
        else{
            printf("\033[41;36;5m谷鄉元昭\033[0m 的攻擊被閃避了!\n");
            Sleep(2000);
            printf("\033[46;37;5m%s\033[0m 展開了反擊!\n",player->name);
            Sleep(2000);
            player_attack_boss(player, &boss, initial);
            if(boss.dead)
            {
                player->gameover = 1;
                return;
            }
        }
        printf("\033[46;37;5m%s\033[0m 對 虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 發動攻擊!\n", player->name);
        Sleep(2000);
        if(!dodge())
        {
            player_attack_boss(player, &boss, initial);
            if(boss.dead)
            {
                player->gameover = 1;
                return;
            }
        }
        else
        {
            printf("\033[46;37;5m%s\033[0m 的攻擊被閃避了!\n", player->name);
            Sleep(2000);
            printf("\033[41;36;5m谷鄉元昭\033[0m 展開了反擊!\n");
            Sleep(2000);
            boss_attack(player, &boss, initial);
            if(player->gameover || boss.dead)
            {
                return;
            }
        }
        Sleep(3000);
        boss.health += 2;
        boss.strength += 2;
        ++cnt;
        if(cnt == 3)
        {
            cnt = 0;
            boss.level += 1;
            system("cls");
            printf("特性發動:\033[43;30;5m<越戰越強‧ 超越>\033[0m --- 虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 的等級提升至%d等!\n", boss.level);
            Sleep(2000);
        }
        printf("特性發動:\033[43;30;5m<越戰越強>\033[0m --- 虛擬主播集團董事長 \033[41;36;5m谷鄉元昭\033[0m 現有%d點生命和%d點攻擊力!\n", boss.health, boss.strength);
        printf("~~~回合結束~~\n");
        system("pause");
    }
}
void game_introduction()
{
    printf("隨著科技的發展，\033[47;31;5m虛擬主播(Vtubers)\033[0m的勢力日漸增長...\n");
    Sleep(2000);
    printf("人們寧可餓死，也要把錢打給虛擬主播們，只為博得她們嫣然一笑。\n");
    Sleep(2000);
    printf("漸漸的，三次元世界的人類逐漸被吸入二次元空間之中。\n");
    Sleep(2000);
    printf("為了挽回一切，人理保障機構的博士 : \033[34;1m羅馬尼‧ 阿基曼\033[0m ，耗盡一切心血創造了你---\n");
    Sleep(2000);
    printf("---\033[46;37;5m決戰用兵器\033[0m。你是\033[32;5m地球上唯一不會被吸入二次元空間，並能與之抗衡\033[0m的實體。\n");
    Sleep(2000);
    printf("去吧!打敗邪惡的Vtuber集團，拯救人理!\n");
    system("pause");
    system("cls");
}
void overall_introduction()
{
    printf("~~~遊戲機制介紹~~~\n");
    Sleep(2000);
    printf("地圖上不被佔領的位置將以\033[47;30;5m'.'\033[0m來表示\n");
    printf("地圖中受\033[47;30;5m戰爭迷霧\033[0m干擾。\n除\033[41;36;5m散發強大氣場的boss\033[0m及\033[46;37;5m自身\033[0m以外，");
    printf("玩家雖能看到物件(以\033[47;30;5m'x'\033[0m表示)，卻無法得知物件種類。\n");
    printf("玩家必須親自拜訪，方能得知物件屬性。\n");
    printf("\033[47;34;5m友善物件\033[0m : 槍枝、村莊 ; \033[47;31;5m惡意物件\033[0m : 陷阱、魔物、boss\n");
    Sleep(4000);
    system("pause");
    printf("玩家每次擊敗魔物, 將能得到\033[32;5m與魔物等級相符的經驗值\033[0m。\n");
    Sleep(2000);
    printf("當\033[32;5m經驗值 = 玩家當前等級\033[0m時，玩家將消耗經驗值而\033[32;5m升級\033[0m，並得到升級獎勵。\n");
    Sleep(2000);
    printf("遊戲勝利條件 : \033[32;5m擊敗最終boss\033[0m\n");
    Sleep(2000);
    printf("由於boss技能特性，故\033[32;5m玩家在等級達到4等以上之前，不得挑戰boss\033[0m\n");
    Sleep(2000);
    system("pause");
    printf("除boss之外的戰鬥，皆為\033[32;5m玩家先攻\033[0m。\n");
    Sleep(2000);
    printf("戰鬥過程，雙方皆有可能觸發迴避，\033[32;5m迴避後將進行反擊\033[0m。\n");
    Sleep(2000);
    printf("\033[32;5m迴避後的反擊為必中攻擊\033[0m\n");
    Sleep(2000);
    printf("~~~機制介紹結束~~~\n");
    system("pause");
    system("cls");
}
void check_object(info *player,info2 *map,int tempx,int tempy)
{
    switch(map->arr[tempx][tempy])
    {
        case 'm':
            battle(player);
            break;
        case 't':
            trap(player);
            break;
        case 'g':
            gun(player);
            break;
        case 'v':
            village(player);
            break;
        case 'b':
            if(player->level < 4)
            {
                printf("你還沒做好準備，請至少升至4等後再來挑戰boss!\n");
                return;
            }
            else
            {
                printf("即將進入boss戰環節，以下為boss的幾種特性:\n");
                Sleep(2000);
                printf("-------------------------------------------\n");
                printf("1.\033[43;30;5m<先聲奪人>\033[0m : boss必定先攻\n");
                Sleep(2000);
                printf("2.\033[43;30;5m<越戰越強>\033[0m : boss的生命和攻擊力將隨著回合推進而增長，每回合增加各2點;等級每3回合增加1級\n");
                Sleep(2000);
                printf("3.\033[43;30;5m<強者特權>\033[0m : 若玩家等級低於boss等級2等以上，則玩家即死\n");
                system("pause");
                battle_boss(player);
            }
    }
}
bool check_level(info player,info3 boss)
{
    if(player.level + 2 < boss.level)
    {
        return 1;
    }
    else
        return 0;
}
bool dodge()
{
    srand((unsigned)time(NULL));
    int k = rand();
    if(k % 10 < 2)//0~9 if 0~1 then success dodge
    {
        return 1;//success rate : 10%
    }
    else
    {
        return 0;
    }
}
void adventure(info *player, info2 *map)
{
    game_introduction();
    overall_introduction();
    //pre-game procedure
    create_map(map);
    settings_before_game(player);
    //start game
    set_up_map_objects(player,map);
    print_map(*player,map);
    while(!player->gameover){
        movement(player, map);
    }
    free(map->arr);
}




















