#include <iostream>
#include <random>

char grid[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

void print_grid (char grid[3][3]){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void computer_move(char grid[3][3]){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 2); // Range 0–2

	int rand_num_one = dist(gen);
	int rand_num_two = dist(gen);
	bool retry = true;

	while(retry){
		if (grid[rand_num_one][rand_num_two] == '-'){
			grid[rand_num_one][rand_num_two] = 'o';
			retry = false;
		} else {
			rand_num_one = dist(gen);
			rand_num_two = dist(gen);
			retry = true;
		}
	}
	print_grid(grid);
}

void accept_move (char grid[3][3]){
	int row, column;
	bool retry = true;

	while (retry){
		std::cout << "Enter the row and the column" << std::endl;
		std::cin >> row;
		std::cin >> column;

		if (grid[row][column] == '-'){
			grid[row][column] = 'x';
			print_grid(grid);
			retry = false;
		} else {
			std::cout << "Invalid Move" << std::endl;
			print_grid(grid);
		}
	}
}

bool check_win(char grid[3][3]) {
    // Check all rows
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != '-') {
            return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != '-') {
            return true;
        }
    }

    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != '-') {
        return true;
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != '-') {
        return true;
    }

    // No win found
    return false;
}

bool is_game_finished (char grid[3][3]){
	for (int i = 0; i < 3; i++ ){
		for(int j = 0; j < 3; j++){
			if (grid[i][j] == '-'){
				return false;
				break;
			}
		}
	}
	return true;
}

int main () {
	print_grid(grid);
	while( !check_win(grid) ){
		accept_move(grid);
		if (is_game_finished(grid)){
			std::cout << "Game Finished, Draw" << std::endl;
		} else if(check_win(grid)){
			std::cout << "Someone Won" << std::endl;
		} else {
			std::cout << "My turn..." << std::endl;
			std::cout << "" << std::endl;
			computer_move(grid);
		}
	}
	return 0;
}
