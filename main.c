#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
//-----------------------------Data Structures----------------------------------
//------------------------------------------------------------------------------

//-----------------------------Dictionary-------------------------------------
// integer Key-Value pair
typedef struct
{
    int key;
    int value;
} int_key_value;

// integer Key-Value pair list
typedef struct
{
    int length;
    int_key_value *array;
} int_dict;

int_dict create_int_dict()
{
    int_dict list;
    list.length = 0;
    list.array = (int_key_value *)malloc(0);
    return list;
}

void free_int_dict(int_dict list)
{
    free(list.array);
}

void add_int_dict(int_dict *list, int key, int value)
{
    list->array[list->length].key = key;
    list->array[list->length].value = value;
    list->length++;
}
bool const_int_dict(int_dict list, int key)
{
    for (int i = 0; i < list.length; i++)
    {
        if (list.array[i].key == key)
        {
            return true;
        }
    }
    return false;
}
// sort from largest to smallest
void sort_int_dict_by_value(int_dict *list)
{
    int_key_value temp;
    for (int i = 0; i < list->length; i++)
    {
        for (int j = 0; j < list->length - 1; j++)
        {
            if (list->array[j].value < list->array[j + 1].value)
            {
                temp = list->array[j];
                list->array[j] = list->array[j + 1];
                list->array[j + 1] = temp;
            }
        }
    }
}
//----------------------------- statistics -------------------------------------
struct statistics
{
    int_dict super_loto_statistics;
    int_dict digital_loto_statistics;
    int_dict chance_ball_statistics;
    int_dict chance_ball_one_plus_statistics;
    int_dict number_ten_statistics;
};
struct statistics create_statistics()
{
    struct statistics stats;
    stats.super_loto_statistics = create_int_dict();
    stats.digital_loto_statistics = create_int_dict();
    stats.chance_ball_statistics = create_int_dict();
    stats.number_ten_statistics = create_int_dict();
    stats.chance_ball_one_plus_statistics = create_int_dict();
    return stats;
}
struct statistics free_statistics(struct statistics stats)
{
    free_int_dict(stats.super_loto_statistics);
    free_int_dict(stats.digital_loto_statistics);
    free_int_dict(stats.chance_ball_statistics);
    free_int_dict(stats.number_ten_statistics);
    free_int_dict(stats.chance_ball_one_plus_statistics);
    return stats;
}
void add_statistics(int_dict *game_statistics, int array[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (const_int_dict(*game_statistics, array[i]))
        {
            int_dict *dict = game_statistics;
            int_key_value *key_value = &dict->array[i];
            key_value->value++;
        }
        else
        {
            add_int_dict(game_statistics, array[i], 1);
        }
    }
}
void print_statistics(int_dict game_statistics)
{
    sort_int_dict_by_value(&game_statistics);
    for (int i = 0; i < game_statistics.length; ++i)
    {
        printf("%d: %d\n", game_statistics.array[i].key, game_statistics.array[i].value);
    }
}

//-----------------------------Points-------------------------------------
struct points
{
    int super_loto_points;
    int digital_loto_points;
    int chhance_ball_points;
    int number_ten_points;
};
struct points create_points()
{
    struct points points;
    points.super_loto_points = 0;
    points.digital_loto_points = 0;
    points.chhance_ball_points = 0;
    points.number_ten_points = 0;
    return points;
}
int total_points(struct points points)
{
    int points_sum = 0;
    points_sum += points.super_loto_points;
    points_sum += points.digital_loto_points;
    points_sum += points.chhance_ball_points;
    points_sum += points.number_ten_points;
    return points_sum;
}
// function prototypes
int get_seed();
int get_int_by_range(int min, int max);
int get_int();
void get_int_array_by_range(int array[], int size, int min, int max);
void generate_random_array(int array[], int size, int min, int max);
void short_by_int_array(int array[], int length);
int compare_int_arrays(int array1[], int array2[], int length, int length2);
int calculate_points(int matches, int score_coefficient, int condition);
void super_lotto();
void digital_lotto();
void chance_ball();
void number_ten();
void main_menu();
void games_menu();
void statistics_menu();
void print_inputs(int user_inputs[], int computer_inputs[], int user_inputs_length, int computer_inputs_length);

// variables
struct statistics stats;
struct points points;

// free memory
void free_memory()
{
    free_statistics(stats);
}

// Function: main
int main()
{
    stats = create_statistics();
    points = create_points();
    int seed = get_seed();
    system("cls");
    srand(seed);
    while (true)
    {
        main_menu();
    }
    return 0;
}

// function that gets the seed value from the user
int get_seed()
{
    printf("Enter a seed value: ");
    int seed = get_int();
    return seed;
}

// function that takes an int value in a range from the user
int get_int_by_range(int min, int max)
{
    int value;
    while (scanf("%d", &value) != 1 || value < min || value > max)
    {
        printf("Invalid input. Please try again: ");
        while (getchar() != '\n');
    }
    return value;
}
// function that gets an integer from the user

int get_int()
{
    return get_int_by_range(INT_MIN, INT_MAX);
}

// function that takes a different int array from the user

void get_int_array_by_range(int array[], int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        printf("Enter value %d: ", i + 1);
        array[i] = get_int_by_range(min, max);
        for (int j = 0; j < i; j++)
        {
            if (array[i] == array[j])
            {
                printf("Value %d is repeated. Please try again: ", i + 1);
                i--;
                break;
            }
        }
    }
}

// function that generates a random array of non-identical integers in a range
void generate_random_array(int array[], int size, int min, int max)
{
    int i = 0;
    while (i < size)
    {
        int random = rand() % (max - min + 1) + min;
        int j = 0;
        while (j < i)
        {
            if (array[j] == random)
            {
                break;
            }
            j++;
        }
        if (j == i)
        {
            array[i] = random;
            i++;
        }
    }
}

// function that sorts integer array with bubble algorithm
void short_by_int_array(int array[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            int temp;
            if (array[i] < array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

// Function that compares two integer arrays and returns the number of matches
int compare_int_arrays(int array1[], int array2[], int length, int length2)
{
    int matches = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            if (array1[i] == array2[j])
            {
                matches++;
                printf("%d ", array1[i]);
            }
        }
    }
    return matches;
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------Games--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

// function that calculates points
int calculate_points(int matches, int score_coefficient, int condition)
{
    if (matches > condition)
    {
        return pow(matches + 2, score_coefficient);
    }
    return 0;
}

// Game function
void game(int max, int *point, int_dict *gameStats, int score_coefficient, int user_len, int computer_len, char *gameName, int condition, int a)
{
    printf("-------------------%s-------------------\n", gameName);
    int user_inputs[user_len];
    int computer_inputs[computer_len];
    get_int_array_by_range(user_inputs, user_len, 1, max);
    generate_random_array(computer_inputs, computer_len, 1, max);
    short_by_int_array(user_inputs, user_len);
    short_by_int_array(computer_inputs, computer_len);
    print_inputs(user_inputs, computer_inputs, user_len, computer_len);
    printf("Matches:");
    int matches = compare_int_arrays(user_inputs, computer_inputs, user_len, computer_len);
    printf("\n");
    printf("%s: %d\n", "Number of matches", matches);
    printf("%s: %d\n", "Points", calculate_points(matches - a, score_coefficient, condition));
    *point += calculate_points(matches - a, score_coefficient, condition);
    printf("%s: %d\n", "Total points", total_points(points));
    add_statistics(gameStats, computer_inputs, computer_len);
}

// print user inputs and computer inputs
void print_inputs(int user_inputs[], int computer_inputs[], int user_inputs_length, int computer_inputs_length)
{
    printf("User inputs: ");
    for (int i = 0; i < user_inputs_length; i++)
    {
        printf("%d ", user_inputs[i]);
    }
    printf("\n");
    printf("Computer inputs: ");
    for (int i = 0; i < computer_inputs_length; i++)
    {
        printf("%d ", computer_inputs[i]);
    }
    printf("\n");
}

// Super Lotto game function
void super_lotto()
{
    game(54, &points.super_loto_points, &stats.super_loto_statistics, 2, 6, 6, "Super Lotto", 2, 0);
}

// Digital Lotto game function
void digital_lotto()
{
    game(49, &points.digital_loto_points, &stats.digital_loto_statistics, 2, 6, 6, "Digital Lotto", 2, 0);
}

// Chance game function
void chance_ball()
{

    printf("-------------------Chance Ball Game-------------------\n");
    int length = 5;
    int ball[length];
    int computer[length];
    printf("+1 number: ");
    int one_plus = get_int_by_range(0, 14);
    int computer_one_plus = rand() % (14 - 0 + 1) + 0;
    add_statistics(&stats.chance_ball_one_plus_statistics, &computer_one_plus, 1);
    get_int_array_by_range(ball, length, 1, 34);
    generate_random_array(computer, length, 1, 34);
    add_statistics(&stats.chance_ball_statistics, computer, length);
    short_by_int_array(ball, length);
    short_by_int_array(computer, length);

    print_inputs(ball, computer, length, length);
    printf("Computer +1 number: %d\n", computer_one_plus);
    printf("Matches:");
    int matches = compare_int_arrays(ball, computer, length, length);
    if (one_plus == computer_one_plus)
    {
        matches++;
    }
    printf("\n");
    printf("%s: %d\n", "Number of matches", matches);
    printf("%s: %d\n", "Points", calculate_points(matches, 2, 1));
    points.chhance_ball_points += calculate_points(matches, 2, 1);
    printf("%s: %d\n", "Total points", total_points(points));
}

// Number Ten game function
void number_ten()
{
    game(80, &points.number_ten_points, &stats.number_ten_statistics, 2, 10, 22, "Number Ten", 5, 2);
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------Menu---------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

// Main menu function
void main_menu()
{
    printf("-------------------Main Menu-------------------\n");
    printf("1. Games\n");
    printf("2. Statistics\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
    int option = get_int_by_range(1, 3);
    system("cls");
    switch (option)
    {
    case 1:
        games_menu();
        break;
    case 2:
        statistics_menu();
        break;
    case 3:
        free_memory();
        exit(0);
    default:
        printf("Invalid option!\n");
        main_menu();
        break;
    }
}

// Games menu function
void games_menu()
{
    printf("-------------------Games Menu-------------------\n");
    printf("1. Super Lotto\n");
    printf("2. Digital Lotto\n");
    printf("3. Chance Ball\n");
    printf("4. Number Ten\n");
    printf("5. Back\n");
    printf("Total points: %d\n", total_points(points));
    printf("Choose an option: ");
    int option = get_int_by_range(1, 5);
    system("cls");
    switch (option)
    {
    case 1:
        super_lotto();
        break;
    case 2:
        digital_lotto();
        break;
    case 3:
        chance_ball();
        break;
    case 4:
        number_ten();
        break;
    case 5:
        main_menu();
        break;
    default:
        printf("Invalid option!\n");
        games_menu();
        break;
    }
}

// Statistics menu function
void statistics_menu()
{
    printf("-------------------Statistics Menu-------------------\n");
    printf("1. Super Lotto Statistics\n");
    printf("2. Digital Lotto Statistics\n");
    printf("3. Chance Ball Statistics\n");
    printf("4. Number Ten Statistics\n");
    printf("5. Back\n");
    printf("Choose an option: ");
    int option = get_int_by_range(1, 5);
    system("cls");
    switch (option)
    {
    case 1:
        print_statistics(stats.super_loto_statistics);
        break;
    case 2:
        print_statistics(stats.digital_loto_statistics);
        break;
    case 3:
        print_statistics(stats.chance_ball_statistics);
        printf("\n");
        printf("+1 statistics:\n");
        print_statistics(stats.chance_ball_one_plus_statistics);
        break;
    case 4:
        print_statistics(stats.number_ten_statistics);
        break;
    case 5:
        main_menu();
        break;
    default:
        printf("Invalid option!\n");
        statistics_menu();
        break;
    }
}