import messages


def sign_up_validator(auth_customer, cmd_tokens):
    # disregard already signed in users
    if auth_customer:
        return False, messages.USER_ALREADY_SIGNED_IN
    # sign_up <email> <password> <first_name> <last_name> <plan_id>
    elif len(cmd_tokens) == 6:
        return True, None
    else:
        return False, messages.CMD_NOT_ENOUGH_ARGS % 5


def sign_in_validator(auth_customer, cmd_tokens):
    # disregard already signed in users
    if auth_customer:
        if auth_customer.email == cmd_tokens[1]:
            return None, messages.USER_ALREADY_SIGNED_IN
        else:
            return None, messages.USER_OTHER_SIGNED_IN

    # sign_in <email> <password>
    elif len(cmd_tokens) == 3:
        return True, None
    else:
        return False, messages.CMD_NOT_ENOUGH_ARGS % 2


"""
    This validator is basic validator that returns (True, None) 
    when a user is authenticated and the number of command tokens is 1.
    Returns (False, <message>) otherwise.
"""


def basic_validator(auth_customer, cmd_tokens):
    # only accept signed in users
    if auth_customer:
        return True, None
    elif not auth_customer and len(cmd_tokens) == 1:
        return False, messages.USER_NOT_AUTHORIZED
    else:
        return False, messages.CMD_INVALID_ARGS


def sign_out_validator(auth_customer, cmd_tokens):
    return basic_validator(auth_customer, cmd_tokens)


def quit_validator(cmd_tokens):
    if len(cmd_tokens) == 1:
        return True, None
    else:
        return False, messages.CMD_INVALID_ARGS


def show_plans_validator(auth_customer, cmd_tokens):
    return basic_validator(auth_customer, cmd_tokens)


def show_subscription_validator(auth_customer, cmd_tokens):
    return basic_validator(auth_customer, cmd_tokens)


def watched_movies_validator(auth_customer, cmd_tokens):
    if not auth_customer:
        return False, messages.USER_NOT_AUTHORIZED
    elif len(cmd_tokens) <= 1:
        return False, messages.CMD_NOT_ENOUGH_ARGS_AT_LEAST % 1
    else:
        return True, None


def subscribe_validator(auth_customer, cmd_tokens):
    # only accept signed in users
    if not auth_customer:
        return False, messages.USER_NOT_AUTHORIZED
    # subscribe <plan_id>
    elif len(cmd_tokens) == 2:
        return True, None
    else:
        return False, messages.CMD_NOT_ENOUGH_ARGS % 1


def search_for_movies_validator(auth_customer, cmd_tokens):
    # only accept signed in users
    if not auth_customer:
        return False, messages.USER_NOT_AUTHORIZED
    # search_for_movies <keyword_1> <keyword_2> <keyword_3> ... <keyword_n>
    elif len(cmd_tokens) > 1:
        return True, None
    else:
        return False, messages.CMD_NOT_ENOUGH_ARGS_AT_LEAST % 1


def suggest_movies_validator(auth_customer, cmd_tokens):
    return basic_validator(auth_customer, cmd_tokens)
