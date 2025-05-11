class SocietyMaintenanceExpertSystem:
    def __init__(self):
        # Knowledge base for water supply and light issues
        self.knowledge_base = {
            "water_supply_monday": {
                "questions": [
                    ("Is the water pump malfunctioning?", "The water pump may be faulty. Check for mechanical/electrical issues."),
                    ("Is the water reservoir empty?", "The water reservoir may need to be refilled."),
                    ("Is there a leak in the water pipe?", "Check the water pipes for any leaks."),
                    ("Was there a power outage?", "Power failure may have caused the pump to stop working.")
                ],
                "resolved": False
            },
            "common_passage_lights": {
                "questions": [
                    ("Was there a power outage?", "Check if the area had a power failure."),
                    ("Are the light bulbs burnt out?", "Replace the burnt-out light bulbs."),
                    ("Is there faulty wiring?", "Inspect the electrical wiring for faults.")
                ],
                "resolved": False
            }
        }

    def ask_question(self, question):
        """Ask the user a yes/no question and return the response"""
        while True:
            response = input(f"{question} (y/n): ").strip().lower()
            if response in ['y', 'n']:
                return response == 'y'
            print("Invalid input. Please enter 'y' or 'n'.")

    def diagnose_issue(self, issue_type):
        """Diagnose either water supply or light issue based on the issue type"""
        issue = self.knowledge_base.get(issue_type)
        if not issue:
            print("Issue type not recognized.")
            return
        
        print(f"\nDiagnosing issue: {issue_type.replace('_', ' ').capitalize()}...\n")
        for question, recommendation in issue["questions"]:
            if self.ask_question(question):
                print(f"Recommendation: {recommendation}")
        
        issue["resolved"] = True
        print("\nDiagnosis Complete.\n")

    def handle_query(self):
        """Handle user queries and provide diagnoses"""
        while True:
            print("\nChoose an issue to diagnose:")
            print("1. Why was there no water supply on Monday?")
            print("2. Why were there no lights in the common passage?")
            print("3. Exit")
            choice = input("Enter choice (1-3): ")

            if choice == '1':
                self.diagnose_issue("water_supply_monday")
            elif choice == '2':
                self.diagnose_issue("common_passage_lights")
            elif choice == '3':
                print("Exiting the system. Thank you!")
                break
            else:
                print("Invalid choice. Please choose again.")

# Driver code
if __name__ == "__main__":
    system = SocietyMaintenanceExpertSystem()
    system.handle_query()
