import argparse
import random


def create_available_space(board_size):
    mid_place = (board_size - 1) / 2

    range_list = range(board_size)

    available_space = [(x, y) for x in range_list for y in range_list]
    available_space.remove((mid_place, mid_place))

    return available_space


def print_player(type, coord):
    print ("%d%s%s%s%d%s%d" % (priority, delimiter, type, delimiter, coord[0], delimiter, coord[1]))


def str2bool(v):
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')

parser = argparse.ArgumentParser()
parser.add_argument("--boardSize", help="The length of the board square.", type=int, choices=xrange(3, 27, 2), default=3)
parser.add_argument("--playerCount", help="The total player count.", type=int, choices=xrange(1, 100), default=2)
parser.add_argument("--dummyOnHill", help="If true, the parser will add a Dummy on top of the hill.", type=str2bool, default=False)

args = parser.parse_args()
board_size = args.boardSize         # Max : 25
player_count = args.playerCount     # Max : 100 (99 actually, may be +1 Dummy on hill)
dummy_on_hill = args.dummyOnHill

available_space = create_available_space(board_size)

if player_count > len(available_space):
    raise argparse.ArgumentTypeError("Not enough space for %d players. Total space: %d" %
                                     (player_count, len(available_space)))

player_type_list = ["Berserk", "Tracer", "Ambusher", "Pacifist", "Dummy"]

print "Board Size: %d" % board_size
print "Player Count: %d" % player_count

delimiter = '::'

if dummy_on_hill:
    player_count -= 1

for priority in range(player_count):
    player_type = random.choice(player_type_list)
    player_coord = random.choice(available_space)

    print_player(player_type, player_coord)

    available_space.remove(player_coord)

if dummy_on_hill:
    priority = player_count
    mid_place = (board_size - 1) / 2

    print_player("Dummy", (mid_place, mid_place))