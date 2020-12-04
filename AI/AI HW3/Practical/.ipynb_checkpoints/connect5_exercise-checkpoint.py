import numpy as np
import random
import pygame
import sys

GREY = (120, 120, 120)
BLUE = (43, 30, 186)
RED = (135, 7, 28)
RED_WIN = (138, 99, 117)
BLUE_WIN = (99, 95, 135)
BLACK = (0, 0, 0)
WHITE = (220, 220, 220)

ROW_COUNT = 6
COLUMN_COUNT = 10

PLAYER1 = 0
PLAYER2 = 1

EMPTY = 0
PLAYER1_PIECE = 1
PLAYER2_PIECE = 2

WINDOW_LENGTH = 5


# Rendering
def create_board():
    board = np.zeros((ROW_COUNT, COLUMN_COUNT))
    return board


def draw_board(board):
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT):
            pygame.draw.rect(screen, GREY, (c * SQUARESIZE, r * SQUARESIZE + SQUARESIZE, SQUARESIZE, SQUARESIZE))
            if r % 2:
                pygame.draw.circle(screen, BLUE_WIN, (
                    int(c * SQUARESIZE + SQUARESIZE / 2), int(r * SQUARESIZE + SQUARESIZE + SQUARESIZE / 2)), RADIUS)
            else:
                pygame.draw.circle(screen, RED_WIN, (
                    int(c * SQUARESIZE + SQUARESIZE / 2), int(r * SQUARESIZE + SQUARESIZE + SQUARESIZE / 2)), RADIUS)

    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT):
            if board[r][c] == PLAYER1_PIECE:
                pygame.draw.circle(screen, RED, (
                    int(c * SQUARESIZE + SQUARESIZE / 2), height - int(r * SQUARESIZE + SQUARESIZE / 2)), RADIUS)
            elif board[r][c] == PLAYER2_PIECE:
                pygame.draw.circle(screen, BLUE, (
                    int(c * SQUARESIZE + SQUARESIZE / 2), height - int(r * SQUARESIZE + SQUARESIZE / 2)), RADIUS)
    pygame.display.update()


def print_board(board):
    print(np.flip(board, 0))


# Logic
def get_next_open_row(board, col):
    for r in range(ROW_COUNT):
        if board[r][col] == 0:
            return r


def drop_piece(board, row, col, piece):
    board[row][col] = piece


def is_valid_location(board, col):
    return board[ROW_COUNT - 1][col] == 0


def get_valid_locations(board):
    valid_locations = []
    for col in range(COLUMN_COUNT):
        if is_valid_location(board, col):
            valid_locations.append(col)
    return valid_locations


def is_terminal_node(board):
    return winning_move(board, PLAYER1_PIECE)[0] or winning_move(board, PLAYER2_PIECE)[0] or len(
        get_valid_locations(board)) == 0


def winning_move(board, piece):
    # Check horizontal locations for win
    for c in range(COLUMN_COUNT - 4):
        for r in range(ROW_COUNT):
            if board[r][c] == piece and board[r][c + 1] == piece and board[r][c + 2] == piece and board[r][
                c + 3] == piece and board[r][c + 4] == piece:
                print(f"(r, c) = ({r}, {c + 2})")
                if r % 2:
                    return True, 0
                else:
                    return True, 1

    # Check vertical locations for win
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT - 4):
            if board[r][c] == piece and board[r + 1][c] == piece and board[r + 2][c] == piece and board[r + 3][
                c] == piece and board[r + 4][c] == piece:
                print(f"(r, c) = ({r + 2}, {c})")
                if (r + 2) % 2:
                    return True, 0
                else:
                    return True, 1

    # Check positively sloped diaganols
    for c in range(COLUMN_COUNT - 4):
        for r in range(ROW_COUNT - 4):
            if board[r][c] == piece and board[r + 1][c + 1] == piece and board[r + 2][c + 2] == piece and board[r + 3][
                c + 3] == piece and board[r + 4][c + 4] == piece:
                print(f"(r, c) = ({r + 2}, {c + 2})")
                if (r + 2) % 2:
                    return True, 0
                else:
                    return True, 1
    # Check negatively sloped diaganols
    for c in range(COLUMN_COUNT - 4):
        for r in range(4, ROW_COUNT):
            if board[r][c] == piece and board[r - 1][c + 1] == piece and board[r - 2][c + 2] == piece and board[r - 3][
                c + 3] == piece and board[r - 4][c + 4] == piece:
                print(f"(r, c) = ({r - 2}, {c + 2})")
                if (r - 2) % 2:
                    return True, 0
                else:
                    return True, 1
    return False, 0


# Game
# HINT: You need to have a minimax function that uses an scoring policy function.

def minimax(board, depth, player):
    pass


def score_position(board, piece):
    pass


board = create_board()
print_board(board)
game_over = False

pygame.init()

SQUARESIZE = 100

width = COLUMN_COUNT * SQUARESIZE
height = (ROW_COUNT + 1) * SQUARESIZE

size = (width, height)

RADIUS = int(SQUARESIZE / 2 - 5)

screen = pygame.display.set_mode(size)
draw_board(board)
pygame.display.update()

myfont = pygame.font.SysFont("monospace", 75)

turn = random.randint(PLAYER1, PLAYER2)

while not game_over:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    if len(get_valid_locations(board)) == 0:
        label = myfont.render("TIE!", 1, WHITE)
        screen.blit(label, (40, 10))
        game_over = True
        draw_board(board)

    # # Swap commented below lines for lines 203-222 to play yourself as PLAYER1
    #     if event.type == pygame.MOUSEMOTION:
    #         pygame.draw.rect(screen, BLACK, (0, 0, width, SQUARESIZE))
    #         posx = event.pos[0]
    #         if turn == PLAYER1:
    #             pygame.draw.circle(screen, RED, (posx, int(SQUARESIZE / 2)), RADIUS)
    #
    #     pygame.display.update()
    #
    #     if event.type == pygame.MOUSEBUTTONDOWN:
    #         pygame.draw.rect(screen, BLACK, (0, 0, width, SQUARESIZE))
    #         # print(event.pos)
    #         # Ask for Player 1 Input
    #         if turn == PLAYER1:
    #             posx = event.pos[0]
    #             col = int(math.floor(posx / SQUARESIZE))
    #             if is_valid_location(board, col):
    #                 row = get_next_open_row(board, col)
    #                 drop_piece(board, row, col, PLAYER1_PIECE)
    #
    #                 if winning_move(board, PLAYER1_PIECE) == (True, 0):
    #                     label = myfont.render("Player 1 wins!", 1, WHITE)
    #                     screen.blit(label, (40, 10))
    #                     game_over = True
    #                 elif winning_move(board, PLAYER1_PIECE) == (True, 1):
    #                     label = myfont.render("Player 1 loses!", 1, WHITE)
    #                     screen.blit(label, (40, 10))
    #                     game_over = True
    #
    #                 turn = 1 - turn
    #                 print_board(board)
    #                 draw_board(board)

    if turn == PLAYER1 and not game_over:
        col = random.choice(get_valid_locations(board))
        # col, minimax_score = minimax(...) # YOU SHOULD DO THIS LINE.

        if is_valid_location(board, col):
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, PLAYER1_PIECE)

            if winning_move(board, PLAYER1_PIECE) == (True, 0):
                label = myfont.render("Player 1 wins!", 1, WHITE)
                screen.blit(label, (40, 10))
                game_over = True
            elif winning_move(board, PLAYER1_PIECE) == (True, 1):
                label = myfont.render("Player 1 loses!", 1, WHITE)
                screen.blit(label, (40, 10))
                game_over = True

            turn = 1 - turn
            print_board(board)
            draw_board(board)

    if turn == PLAYER2 and not game_over:
        col = random.choice(get_valid_locations(board))
        # col, minimax_score = minimax(...) # YOU SHOULD DO THIS LINE.

        if is_valid_location(board, col):
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, PLAYER2_PIECE)

            if winning_move(board, PLAYER2_PIECE) == (True, 1):
                label = myfont.render("Player 2 wins!", 1, WHITE)
                screen.blit(label, (40, 10))
                game_over = True
            elif winning_move(board, PLAYER2_PIECE) == (True, 0):
                label = myfont.render("Player 2 loses!", 1, WHITE)
                screen.blit(label, (40, 10))
                game_over = True

            turn = 1 - turn
            print_board(board)
            draw_board(board)

    if game_over:
        pygame.time.wait(8000)  ## 5000 -> 0 IF YOU WANT THE GAME TO QUIT IMMEDIATELY
