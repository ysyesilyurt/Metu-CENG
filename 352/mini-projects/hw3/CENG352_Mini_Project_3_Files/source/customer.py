class Customer:
    def __init__(self, customer_id=0, email="", first_name="", last_name="", session_count="", plan_id=0):
        self.customer_id = customer_id
        self.email = email
        self.first_name = first_name
        self.last_name = last_name
        self.session_count = session_count
        self.plan_id = plan_id

    def __str__(self):
        return '%s %s (%s)' % (self.first_name, self.last_name, self.email)
