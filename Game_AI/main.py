from tictactoe import TicTacToe
import math
import random
import time


def minimax(board, depth, maximizing_player, ai_player):
    opponent = 'O' if ai_player == 'X' else 'X'
    if board.current_winner == ai_player:
        return {'position': None, 'score': 1 * (depth + 1)}
    elif board.current_winner == opponent:
        return {'position': None, 'score': -1 * (depth + 1)}
    elif len(board.available_moves()) == 0:
        return {'position': None, 'score': 0}

    if maximizing_player:
        best_score = -math.inf
        best_move = None
        for move in board.available_moves():
            board.make_move(move, ai_player)
            sim_score = minimax(board, depth - 1, False, ai_player)['score']
            board.undo_move(move)
            if sim_score > best_score:
                best_score = sim_score
                best_move = move
    else:
        best_score = math.inf
        best_move = None
        for move in board.available_moves():
            board.make_move(move, opponent)
            sim_score = minimax(board, depth - 1, True, ai_player)['score']
            board.undo_move(move)
            if sim_score < best_score:
                best_score = sim_score
                best_move = move

    return {'position': best_move, 'score': best_score}

def minimax_with_alpha_beta(board, depth, alpha, beta, maximizing_player, ai_player):
    opponent = 'O' if ai_player == 'X' else 'X'
    if board.current_winner == ai_player:
        return {'position': None, 'score': 1 * (depth + 1)}
    elif board.current_winner == opponent:
        return {'position': None, 'score': -1 * (depth + 1)}
    elif len(board.available_moves()) == 0:
        return {'position': None, 'score': 0}

    if maximizing_player:
        best_score = -math.inf
        best_move = None
        for move in board.available_moves():
            board.make_move(move, ai_player)
            sim_score = minimax_with_alpha_beta(board, depth - 1, alpha, beta, False, ai_player)['score']
            board.undo_move(move)
            if sim_score > best_score:
                best_score = sim_score
                best_move = move
            alpha = max(alpha, sim_score)
            if beta <= alpha:
                break
    else:
        best_score = math.inf
        best_move = None
        for move in board.available_moves():
            board.make_move(move, opponent)
            sim_score = minimax_with_alpha_beta(board, depth - 1, alpha, beta, True, ai_player)['score']
            board.undo_move(move)
            if sim_score < best_score:
                best_score = sim_score
                best_move = move
            beta = min(beta, sim_score)
            if beta <= alpha:
                break

    return {'position': best_move, 'score': best_score}


def play_game_ai_moves_first():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    first_move = True

    letter = 'O'  # AI player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # AI's turn
            if first_move:
                square = random.randint(0, 8)
                first_move = False
            else:
                square = minimax_with_alpha_beta(game, len(game.available_moves()), -math.inf, math.inf, True, 'O')['position']
            if square is None:
                print("\nGame is a draw!")
                break
            game.make_move(square, letter)
            print(f"\nAI (O) chooses square {square + 1}")
        else:
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")

def play_game_human_vs_human():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    letter = 'O'  # Human (O) player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # Human (O)'s turn
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

                if square is None:
                    print("\nGame is a draw!")
                    break
                game.make_move(square, letter)
                print(f"\nAI (O) chooses square {square + 1}")
        else:
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")

def play_game_human_moves_first():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    letter = 'X'  # Human player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # AI's turn
            square = minimax_with_alpha_beta(game, len(game.available_moves()), -math.inf, math.inf, True, 'O')['position']
            if square is None:
                print("\nGame is a draw!")
                break
            game.make_move(square, letter)
            print(f"\nAI (O) chooses square {square + 1}")
        else:
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")

def play_game_ai_moves_first():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    first_move = True

    letter = 'O'  # AI player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # AI's turn
            if first_move:
                square = random.randint(0, 8)
                first_move = False
            else:
                square = minimax_with_alpha_beta(game, len(game.available_moves()), -math.inf, math.inf, True, 'O')['position']
            if square is None:
                print("\nGame is a draw!")
                break
            game.make_move(square, letter)
            print(f"\nAI (O) chooses square {square + 1}")
        else:
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")

def play_game_human_vs_human():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    letter = 'O'  # Human (O) player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # Human (O)'s turn
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

                if square is None:
                    print("\nGame is a draw!")
                    break
                game.make_move(square, letter)
                print(f"\nAI (O) chooses square {square + 1}")
        else:
            valid_square = False
            while not valid_square:
                square = input(f"\n{letter}'s turn. Input move (1-9): ")
                try:
                    square = int(square) - 1
                    if square not in game.available_moves():
                        raise ValueError
                    valid_square = True
                    game.make_move(square, letter)
                except ValueError:
                    print("\nInvalid square. Try again.")

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")

def play_game_ai_vs_ai():

    game = TicTacToe()
    print("\nInitial Board:")
    game.print_board()

    first_move = True

    letter = 'O'  # AI (O) player starts first.
    while game.empty_squares_available():
        if letter == 'O':  # AI (O)'s turn
            if first_move:
                square = random.randint(0, 8)
                first_move = False
            else:
                square = minimax_with_alpha_beta(game, len(game.available_moves()), -math.inf, math.inf, True, 'O')['position']
            if square is None:
                print("\nGame is a draw!")
                break
            game.make_move(square, letter)
            print(f"\nAI (O) chooses square {square + 1}")
            time.sleep(0.75)
        else:
            square = minimax_with_alpha_beta(game, len(game.available_moves()), -math.inf, math.inf, True, 'O')['position']
            if square is None:
                print("\nGame is a draw!")
                break
            game.make_move(square, letter)
            print(f"\nAI (X) chooses square {square + 1}")
            time.sleep(0.75)

        game.print_board()

        if game.current_winner:
            print(f"\n{letter} wins!")
            break

        letter = 'O' if letter == 'X' else 'X'  # Switch turns.
    else:
        print("\nIt's a draw!")


if __name__ == '__main__':

    print("""
Modes of play available:

    hh: Hooman vs. hooman
    ha: Hooman vs. AI
    ah: AI vs. Hooman - AI makes first move
    aa: AI vs. AI""")

    valid_move = False
    while not valid_move:
        mode = input("\nEnter preferred mode of play (e.g., aa): ")
        try:
            if mode not in ["hh", "ha", "ah", "aa"]:
                raise ValueError
            valid_move = True
            if mode == "hh":
                play_game_human_vs_human()
            elif mode == "ha":
                play_game_human_moves_first()
            elif mode == "ah":
                play_game_ai_moves_first()
            else:
                play_game_ai_vs_ai()
        except ValueError:
            print("\nInvalid option entered. Try again.")

