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
    printf("�п�ܱz��¾�~~ �̼Ʀr��d��¾�~����:\n");
    while(1){
        printf("1.\033[43;30;5m�g�Ԥh\033[0m 2.\033[43;31;5m�l�尭\033[0m 3.\033[43;32;5m'��'�ѥ��l\033[0m : ");
        int option;
        scanf("%d", &option);
        printf("\n");
        switch(option){
            case 1:
                printf("\033[43;30;5m�g�Ԥh<���ԧJ�Ǵ�>\033[0m : ��þ���ܤ��b�H�b�����^���C�]��X���Ө���z�����d�l���Ԫ��j�P���c�A�C�����|�N�|����k����i\n�C");
                printf("�M�ӡA�L��V�Ҧ������L���W���A�̫�H�@�L�����������첽���C\n");
                printf("�Q�ʧޯ� : \033[43;30;5m<�԰����E ������>\033[0m\n");
                printf("�u�@�߷R���H���N�ӨϧA�z�ߤ��n�C���ԧJ�Ǵ��b�x���ɶi�J�g�ɪ��A�A");
                printf("���ԧJ�Ǵ�����q���ܹs�I�H�U�A�N�o�ʦ��ĪG�A��_�԰��}�l�e����q�A�åH���������O�԰��C\n");
                printf("�M�ӡA�԰�������A���ԧJ�Ǵ�����q�N���ܤ@�I�A�B�����O�^�k���`�C\n");
                printf("�`�N : ���ޯ�b����C��������Ĳ�o�T���C\n");
                printf("�A���`�N : �Ĩ쳴���P��(����)�L�kĲ�o���ޯ�!\n");
                if(are_you_sure())
                {
                    player->role = 1;
                    player->passive_ability = 3;
                    return;
                }
                break;
            case 2:
                printf("\033[43;31;5m�l�尭<���ԭ}�̺�>\033[0m : ���ԭ}�̺��O�@�W����ۤH���A�媺�c�]�C���F�i�H�z�L���M�`���覡�����L���ͩR�A\n");
                printf("�L����A�媺�x���]�ϥL�i�H�����a�ޱ��L�H���ߴ��P���� �� �p�P�L�ޱ��ۤv�@��²��C\n");
                printf("�Q�ʧޯ� : \033[43;31;5m<��⫴��>\033[0m\n");
                printf("�Q����ͪ����ԭ}�̺��b�԰��ӧQ�ɡA�i�H�Ⱞ������Ҵݯd����G���ܰ��U�C\n");
                printf("�C���ԭ}�̺����ѹ��A�N��o����l�ͩR*0.5������q\n");
                if(are_you_sure())
                {
                    player->role = 2;
                    player->passive_ability = 1;
                    return;
                }
                break;
            case 3:
                printf("\033[43;32;5m'��'�ѥ��l<helloworld>\033[0m : ��u�t�A����W����T�u�{�t�A�ꬰ�@�s��ۤH�֪��U�l�A\n");
                printf("�åH�����u��H���ơC�G�����W�u�s�s�u��t�v�C\n");
                printf("�Q�ʧޯ� : \033[43;32;5m<�b�ȵ���>\033[0m\n");
                printf("�s�u�t���ǥ͹���T�����o�B�B�z�۷�ǥX�A�`��H�󦳮Ĳv����q���o�ۤv�Q�n����T�C\n");
                printf("�]���Ahelloworld�����Ԫ��g�����v�T�A�i�H�����ݨ��a�ϥ����C\n");
                printf("�j�K : \033[35;5m'g'\033[0m ; ���� : \033[33;5m't'\033[0m ; ���� \033[32;5m'v'\033[0m ; �����D�� \033[31;5m'm'\033[0m \n");
                if (are_you_sure())
                {
                    player->role = 3;
                    player->passive_ability = 1;
                    return;
                }
                break;
            default:
                system("cls");
                printf("�ڪ����l�n�����}�A�èS���o�ӿﶵ�C\n");
                continue;
        }
    }
}
void name(info *player)
{
    printf("\033[34;1m(ù�����E �����)\033[0m : \033[46;37;5m�M�ԥΧL���N��000\033[0m...���A�O�ɭ����A���@�ӥ��`�I���W�l�F!\n");
    printf("���L�A�W�l���Ӫ����ܡA��_�Ӥ]���Ӥ�K�O~\n\n");
    char arr[100000];
    while(1)
    {
        printf("���� : �п�J\033[32;5m10�Ӧr���H�����^�Ʀr\033[0m : ");
        scanf("%s", arr);
        if(strlen(arr) > 10)
        {
            system("cls");
            printf("�ڪ����l�n�����}�A�èS���o�ӿﶵ�C\n");
        }
        else
            break;
    }
    strcpy(player->name,arr);
    system("cls");
    printf("\033[34;1m(ù�����E �����)\033[0m : �ڷQ���! �N�s�� \033[46;37;5m %s \033[0m �p��? �u�O�Ӧn�W�l�O~\n", arr);
    printf("-------------------------------------------\n");
}
void create_map(info2 *map)
{
    printf("���a�z�n�A���±z��ܳo�ڹC��!\n�b�}�l�C�����e�A�Х���J�a�Ϥj�p\n");
    while(1){
        printf("���� : �a�Ϫ�\033[32;5m���B�e�Ҭ�5�H�W�A1000�H�������\033[0m�C��J�榡:\033[32;5m(��)(space)(�e)(enter)\033[0m\n");
        scanf("%d %d",&map->row,&map->col);
        if(map->row >1000 || map->col >1000 || map->row<5 || map->col <5){
            system("cls");
            printf("�ڪ����l�n�����}�A�èS���o�ӿﶵ�C\n");
        }
        else {
            system("cls");
            printf("�C���N�H\033[32;5m%d��%d\033[0m���a�϶i��, ���۶i�J����]�w���`�C\n",map->row,map->col);
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
    printf("���A�n�T�w�k ! ���U�N������o ?\n");
    int flag;
    while(1)
    {
        printf("1 : �o�ܤֻ��A�Ѥl�N�n�o��  0 : �藍�_�A�����ڭ��� :");
        scanf("%d", &flag);
        switch(flag){
            case 1:
                return 1;
            case 0:
                system("cls");
                return 0;
            default:
                system("cls");
                printf("�ڪ����l�n�����}�A�èS���o�ӿﶵ�C\n");
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
    printf("�A���W�l�O : \033[46;37;5m%s\033[0m   ", player->name);
    switch(player->role){
        case 1:
            printf("�A�O�@�W\033[43;30;5m �g�Ԥh\033[0m\n");
            break;
        case 2:
            printf("�A�O�@�W\033[43;31;5m �l�尭\033[0m\n");
            break;
        case 3:
            printf("�A�O�@�W\033[43;32;5m '��'�ѥ��l\033[0m\n");
            break;
    }
    settle(player);
    printf("\033[42;5m~~~~~~�Y�N�}�l�@�ϤH�z~~~~~~\033[0m\n");
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
        printf("����~�z�w�ɯ�!���Ŵ��ɦ�%d��!\n", player->level);
        printf("�ͩR��_�F2�I�A�����O�W�ɤF1�I!\n");
    }
}
void settle(info *player)
{
    check_level_up(player);
    printf("�A�ثe�֦�~~\n");
    printf("��q : %d ", player->health);
    printf("�����O : %d\n", player->strength);
    printf("���� : %d ", player->level);
    printf("�Z���ɯ��ٮt�g��� : %d�I\n", player->level - player->exp);
    if(player->role == 1){
        if(player->passive_ability > 0)
        {
            printf("�g�Ԫ���ߦb�A�餺�m�ˡC�A�٦�%d���԰���檺���|\n", player->passive_ability);
        }
        else
        {
            printf("�A�w�g�S���԰���檺���|\n");
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
        printf("�ڤ��੹�o�̲��ʡC\n");
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
    printf("���۩�����? 1.�V�W 2.�V�U 3.�V�� 4.�V�k\n");
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
            printf("�ڪ����l�n�����}�A�èS���o�ӿﶵ�C\n");
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
        printf("���ݬݬO�ֽ�쳴����?\n");
        Sleep(2000);
        printf("�������������H�A���h�@�h�����_��C\n");
        Sleep(2000);
        printf("�@�ɳ̫᪺�Ʊ� %s �̲ױĨ쳴���A�Q�ۤv����\n", player->name);
        Sleep(2000);
        printf("�C�������A�@�ɲױN�Q�����D���Ϊv�C");
        Sleep(2000);
        player->gameover = 1;
    }
    else
    {
        printf("���ݬݬO�ֽ�쳴����? �A����%d�I�ˮ`�A�ѤU%d�I��q�A%d�I�����O�C\n", damage, player->health,player->strength);
    }
}
void gun(info *player)
{
    int aux = rand() % 2 + 1;
    player->strength += aux;
    printf("�ߨ�F�@��n�j! �A�u�O�ѿ蠟�H! �A�W�[%d�I�O�q�A�{��%d�I��q�A%d�I�����O\n", aux, player->health ,player->strength);
}
void village(info *player)
{
    int option,test=0;//test if already bought a sword in current visit
        printf("���߱z!�J��F�@�ӧ���!\n");
        Sleep(2000);
	while(1)//do until return(line 105), which is equivalent to existing a function
	{
        printf("�A�Q�b�o�ӧ��������Ǭƻ�? (1:���]; 2: �ͩR�Ŭu; 3:���}����?) : ");
        scanf("%d", &option); //input user's choice
        switch (option)
        {
		case 1://wanna buy a sword
			if(test==1)//already bought a sword
			{
                system("cls");
                printf("���@���A���i�H�g�g�C\n");
                Sleep(2000);
                printf("�@�ӧ����u����]�@����!\n");
                Sleep(2000);
            }
			else//not yet bought a sword
			{
                system("cls");
				player->strength+=1;
				printf("�A�P�����]�O�b�A���W�y��!�A�o��F 1 �I�����O!\n�{�b�A�@�� %d �I�����O!\n",player->strength);
                Sleep(2000);
				test=1;//flag that the user already bought a sword
			}
			break;
		case 2://health regen
			if(player->health>=10)
			{
                system("cls");
				printf("�A���ͩR�Ȥ��p�� 10 �I�A�ͩR�Ŭu�L�k�_�@��!\n");
                Sleep(2000);
			}
			else
			{
                system("cls");
				player->health=10;
				printf("�A�P���쬡�O�b�A���W�y��! �A���ͩR�w��_�� 10 �I!\n");
                Sleep(2000);
			}
			break;
		case 3://leaving the village
            system("cls");
			printf("�A�|�F�A�i��!�O��A�A�O�ڭ̳̫᪺�Ʊ�C\n");
            Sleep(2000);
            printf("�H�ۤ@�}�j���A�o�ӧ����Q�l�J�G�����Ŷ��A�N�������F�C\n");
            Sleep(2000);
            return;
		default://invalid input
            system("cls");
			printf("�ڪ����l�i�঳�}!�S���o�ӿﶵ! (1:���]; 2: �ͩR�Ŭu; 3:���}����) : ");
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
            strcpy(monster.name, "����");
            break;
        case 2:
            strcpy(monster.name, "���");
            break;
        case 3:
            strcpy(monster.name, "����");
            break;
        case 4:
            strcpy(monster.name, "�T��");
            break;
        case 5:
            strcpy(monster.name, "����");
            break;
    }
    return monster;
}
void berserker(info *player,int health)
{
    system("cls");
    printf("\033[41;36;5m \"�گD��Ӿ�!!!\" \033[0m\n");
    //printf("\"�گD��Ӿ�!!!\"\n");
    player->passive_ability -= 1;
    player->health = health;
    player->strength *= 2;
    printf("�A����q�w�k�s�C\n");
    Sleep(2000);
    printf("�ޯ�Ĳ�o  \033[43;30;5m<�԰����E ������>\033[0m: �A�i�J�g�ɪ��A�A�֦�%d�I��q�M%d�I�����O\n", player->health,player->strength);
    printf("�Y�N����Գ�~~\n");
    system("pause");
}
void player_attack(info *player, info3 *monster,info4 initial)
{
            monster->health -= player->strength;
            if(monster->health <= 0)//win
            {
                printf("�D��%d�I��������, �����D�� \033[47;31;5m%s\033[0m �Q���ѤF!\n",player->strength, monster->name);
                system("pause");
                system("cls");
                player->exp += monster->level;
                if(player->strength > initial.player_strength)//if berserkered
                {
                    printf("~~~�g�ɵ����A�A�i�J��z���A~~~\n");
                    player->health = 1;
                    player->strength = initial.player_strength;
                }
                if(player->role == 2)//if vladmir
                {
                    printf("~~~�ޯ�Ĳ�o  \033[43;30;5m<��⫴��>\033[0m: �A����F%d�I�ͩR!~~~\n", initial.monster_health / 2);
                    player->health += initial.monster_health / 2;
                }
                printf("�A�o��F%d�I�g��!\n", monster->level);
                settle(player);
                system("pause");
                system("cls");
                monster->dead = 1;
                return;
            }
            printf("�D��%d�I��������, �����D�� \033[47;31;5m%s\033[0m �ٳѤU%d�I����q\n",player->strength, monster->name, monster->health);
            Sleep(2000);
}
void monster_attack(info *player,info3 *monster,info4 initial){
        player->health -= monster->strength;
        if(player->health <= 0)//lose
        {
            if(player->role == 1 && player->passive_ability > 0)//if is berserker
            {
                berserker(player, initial.player_health);
                printf("�g�ɤ���\033[46;37;5m%s\033[0m��o�l�[�����v!\n", player->name);
                player_attack(player, monster, initial);
            }
            else
            {
                printf("�ܿ�ѡA�z����q�w�k�s�C\n");
                Sleep(2000);
                printf("�������������H�A���h�@�h�����_��C\n");
                Sleep(2000);
                printf("�@�ɳ̫᪺�Ʊ� \033[46;37;5m%s\033[0m �̲׳Q�W�� \033[47;31;5m%s\033[0m �������D�����ѤF\n", player->name, monster->name);
                Sleep(2000);
                printf("�C�������A�@�ɲױN�Q�����D���Ϊv�C");
                player->gameover = 1;
                return;
            }
        }
        else{
            printf("�D��%d�I��������, ���a \033[46;37;5m%s\033[0m �ٳѤU%d�I����q\n",monster->strength, player->name, player->health);
        }
}
void battle(info *player)
{
    info3 monster = generate_monster(*player);
    info4 initial;
    initial.player_health = player->health;
    initial.player_strength = player->strength;
    initial.monster_health = monster.health;
    printf("�A�����e�X�{�F�@������%d�A�W�� : \033[47;31;5m%s\033[0m �������D��! ���֦�%d�I��q��%d�I�����O�C\n", monster.level, monster.name, monster.health, monster.strength);
    system("pause");
    while(1)
    {
        printf("~~~�s�^�X�}�l~~~\n");
        printf("\033[46;37;5m%s\033[0m ������D�� \033[47;31;5m%s\033[0m �o�ʤF����!\n", player->name, monster.name);
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
            printf("\033[46;37;5m%s\033[0m �������Q�{�פF!\n",player->name);
            Sleep(2000);
            printf("\033[47;31;5m%s\033[0m �i�}�F����!\n",monster.name);
            Sleep(2000);
            monster_attack(player, &monster, initial);
            if(player->gameover || monster.dead)
            {
                return;
            }
        }
        printf("�����D�� \033[47;31;5m%s\033[0m �� \033[46;37;5m%s\033[0m �o�ʧ���!\n", monster.name, player->name);
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
            printf("\033[47;31;5m%s\033[0m �������Q�{�פF!\n", monster.name);
            Sleep(2000);
            printf("\033[46;37;5m%s\033[0m �i�}�F����!\n", player->name);
            Sleep(2000);
            player_attack(player, &monster, initial);
            if(monster.dead)
            {
                return;
            }
        }
        printf("~~~�^�X����~~~\n");
        system("pause");
    }
}
info3 generate_boss()
{
    info3 boss;
    boss.health = 20;
    boss.level = 6;
    strcpy(boss.name, "���m���L");
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
                printf("�g�ɤ���\033[46;37;5m%s\033[0m��o�l�[�����v!\n", player->name);
                player_attack(player, boss, initial);
            }
            else
            {
                printf("�b�����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �p�ɫB�몺��դU�A�A���ͩR���k�s�F\n");
                Sleep(2000);
                printf("�������������H�A���h�@�h�����_��C\n");
                Sleep(2000);
                printf("�@�ɳ̫᪺�Ʊ� \033[46;37;5m%s\033[0m �̲׳Q�W�� \033[41;36;5m���m���L\033[0m �������D�����θ��ƪ����ѤF\n", player->name);
                Sleep(4000);
                printf("�C�������A�@�ɲױN�Q�����D���Ϊv�C");
                player->gameover = 1;
                return;
            }
        }
        else{
            printf("�D��%d�I��������, ���a \033[46;37;5m%s\033[0m �ٳѤU%d�I����q\n",boss->strength, player->name, player->health);
        }
}
void player_attack_boss(info *player, info3 *boss,info4 initial){
    boss->health -= player->strength;
        if(boss->health <= 0)//win
        {
            printf("�D��%d�I��������, �����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �Q���ѤF!\n",player->strength);
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
                printf("~~~�ޯ�Ĳ�o  \033[43;30;5m<��⫴��>\033[0m: �A����F%d�I�ͩR!\n", initial.monster_health / 2);
                player->health += initial.monster_health / 2;
            }
            printf("�A�o��F%d�I�g��!\n", boss->level);
            settle(player);
            system("pause");
            system("cls");
            printf("�H�۳̲�boss�����`�A�H���ש�k�������D�����~���A�^�k�T�������{��@��\n");
            Sleep(2000);
            printf("�A���\\�@�ϤF�@��!\n");
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
            printf("�ѰJ�P�±z���C��!\n");
            system("pause");
            system("cls");
            for (int i = 5; i > 0;i--)
            {
                printf("�C���N�b%d��ᵲ��\n", i);
                Sleep(1000);
                system("cls");
            }
                boss->dead = 1;
            player->gameover = 1;
            return;
        }
        printf("�D��%d�I��������,�����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �ٳѤU%d�I����q\n", player->strength, boss->health);
}
void battle_boss(info *player)
{
    info3 boss = generate_boss();
    info4 initial;
    initial.player_health = player->health;
    initial.player_strength = player->strength;
    initial.monster_health = boss.health;
    int cnt = 0;
    printf("�A�����e�X�{�F�@������6�A�W�� : \033[41;36;5m���m���L\033[0m �������D�����θ��ƪ�! ���֦�20�I��q��6�I�����O�C\n");
    system("pause");
    while(1)
    {
        if(check_level(*player,boss))
        {
            printf("�A�M�����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m ���h���t�Z�L�j�A�L�������O�A�L�a�ۮe�C�A�����������Фg�@��ǭ��Ϸ��F\n");
            player->gameover = 1;
            return;
        }
        printf("~~�s�^�X�}�l~~\n");
        printf("�����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �� \033[46;37;5m%s\033[0m �o�ʤF����!\n", player->name);
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
            printf("\033[41;36;5m���m���L\033[0m �������Q�{�פF!\n");
            Sleep(2000);
            printf("\033[46;37;5m%s\033[0m �i�}�F����!\n",player->name);
            Sleep(2000);
            player_attack_boss(player, &boss, initial);
            if(boss.dead)
            {
                player->gameover = 1;
                return;
            }
        }
        printf("\033[46;37;5m%s\033[0m �� �����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �o�ʧ���!\n", player->name);
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
            printf("\033[46;37;5m%s\033[0m �������Q�{�פF!\n", player->name);
            Sleep(2000);
            printf("\033[41;36;5m���m���L\033[0m �i�}�F����!\n");
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
            printf("�S�ʵo��:\033[43;30;5m<�V�ԶV�j�E �W�V>\033[0m --- �����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �����Ŵ��ɦ�%d��!\n", boss.level);
            Sleep(2000);
        }
        printf("�S�ʵo��:\033[43;30;5m<�V�ԶV�j>\033[0m --- �����D�����θ��ƪ� \033[41;36;5m���m���L\033[0m �{��%d�I�ͩR�M%d�I�����O!\n", boss.health, boss.strength);
        printf("~~~�^�X����~~\n");
        system("pause");
    }
}
void game_introduction()
{
    printf("�H�۬�ު��o�i�A\033[47;31;5m�����D��(Vtubers)\033[0m���դO�麥�W��...\n");
    Sleep(2000);
    printf("�H�̹�i�j���A�]�n������������D���̡A�u���ձo�o�̹�M�@���C\n");
    Sleep(2000);
    printf("�������A�T�����@�ɪ��H���v���Q�l�J�G�����Ŷ������C\n");
    Sleep(2000);
    printf("���F���^�@���A�H�z�O�پ��c���դh : \033[34;1mù�����E �����\033[0m �A�Ӻɤ@���ߦ�гy�F�A---\n");
    Sleep(2000);
    printf("---\033[46;37;5m�M�ԥΧL��\033[0m�C�A�O\033[32;5m�a�y�W�ߤ@���|�Q�l�J�G�����Ŷ��A�ï�P���ܿ�\033[0m������C\n");
    Sleep(2000);
    printf("�h�a!���Ѩ��c��Vtuber���ΡA�@�ϤH�z!\n");
    system("pause");
    system("cls");
}
void overall_introduction()
{
    printf("~~~�C�������~~~\n");
    Sleep(2000);
    printf("�a�ϤW���Q���⪺��m�N�H\033[47;30;5m'.'\033[0m�Ӫ��\n");
    printf("�a�Ϥ���\033[47;30;5m�Ԫ��g��\033[0m�z�Z�C\n��\033[41;36;5m���o�j�j�����boss\033[0m��\033[46;37;5m�ۨ�\033[0m�H�~�A");
    printf("���a����ݨ쪫��(�H\033[47;30;5m'x'\033[0m���)�A�o�L�k�o����������C\n");
    printf("���a�����˦۫��X�A���o�������ݩʡC\n");
    printf("\033[47;34;5m�͵�����\033[0m : �j�K�B���� ; \033[47;31;5m�c�N����\033[0m : �����B�]���Bboss\n");
    Sleep(4000);
    system("pause");
    printf("���a�C�������]��, �N��o��\033[32;5m�P�]�����Ŭ۲Ū��g���\033[0m�C\n");
    Sleep(2000);
    printf("��\033[32;5m�g��� = ���a��e����\033[0m�ɡA���a�N���Ӹg��Ȧ�\033[32;5m�ɯ�\033[0m�A�ño��ɯż��y�C\n");
    Sleep(2000);
    printf("�C���ӧQ���� : \033[32;5m���ѳ̲�boss\033[0m\n");
    Sleep(2000);
    printf("�ѩ�boss�ޯ�S�ʡA�G\033[32;5m���a�b���ŹF��4���H�W���e�A���o�D��boss\033[0m\n");
    Sleep(2000);
    system("pause");
    printf("��boss���~���԰��A�Ҭ�\033[32;5m���a����\033[0m�C\n");
    Sleep(2000);
    printf("�԰��L�{�A����Ҧ��i��Ĳ�o�j�סA\033[32;5m�j�׫�N�i�����\033[0m�C\n");
    Sleep(2000);
    printf("\033[32;5m�j�׫᪺��������������\033[0m\n");
    Sleep(2000);
    printf("~~~����е���~~~\n");
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
                printf("�A�٨S���n�ǳơA�Цܤ֤ɦ�4����A�ӬD��boss!\n");
                return;
            }
            else
            {
                printf("�Y�N�i�Jboss�����`�A�H�U��boss���X�دS��:\n");
                Sleep(2000);
                printf("-------------------------------------------\n");
                printf("1.\033[43;30;5m<���n�ܤH>\033[0m : boss���w����\n");
                Sleep(2000);
                printf("2.\033[43;30;5m<�V�ԶV�j>\033[0m : boss���ͩR�M�����O�N�H�ۦ^�X���i�ӼW���A�C�^�X�W�[�U2�I;���ŨC3�^�X�W�[1��\n");
                Sleep(2000);
                printf("3.\033[43;30;5m<�j�̯S�v>\033[0m : �Y���a���ŧC��boss����2���H�W�A�h���a�Y��\n");
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




















