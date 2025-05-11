class EmployeePerformanceExpertSystem:
    def __init__(self):
        self.questions = [
            {"question": "Does the employee consistently meet project deadlines?", "traits": {"reliable": 3}},
            {"question": "Is the employee proactive in taking initiative?", "traits": {"leadership": 2, "innovative": 1}},
            {"question": "Does the employee collaborate effectively in team settings?", "traits": {"teamwork": 3}},
            {"question": "Has the employee received positive client or peer feedback?", "traits": {"communication": 2, "professionalism": 1}},
            {"question": "Does the employee adapt quickly to changes or challenges?", "traits": {"flexibility": 3}},
            {"question": "Does the employee contribute ideas in meetings or brainstorming sessions?", "traits": {"innovative": 3}},
            {"question": "Is the employee punctual and maintains good attendance?", "traits": {"reliable": 2}},
            {"question": "Does the employee handle stress and pressure well?", "traits": {"resilience": 3}},
            {"question": "Does the employee take ownership of their mistakes?", "traits": {"professionalism": 2}},
            {"question": "Does the employee show growth or improvement over time?", "traits": {"learning": 3}},
        ]

        self.scores = {
            "reliable": 0,
            "teamwork": 0,
            "leadership": 0,
            "communication": 0,
            "professionalism": 0,
            "flexibility": 0,
            "innovative": 0,
            "resilience": 0,
            "learning": 0
        }

    def ask_question(self, question):
        while True:
            response = input(f"{question} (y/n): ").strip().lower()
            if response in ['y', 'n']:
                return response == 'y'
            print("Invalid input. Please enter 'y' or 'n'.")

    def evaluate_employee(self):
        print("\n🧠 Welcome to the Employee Performance Evaluation Expert System!")
        print("Answer the following questions based on the employee's behavior:\n")

        for item in self.questions:
            if self.ask_question(item["question"]):
                for trait, score in item["traits"].items():
                    self.scores[trait] += score

        self.show_results()

    def show_results(self):
        print("\n📊 Evaluation Summary:")
        sorted_traits = sorted(self.scores.items(), key=lambda x: x[1], reverse=True)

        for trait, score in sorted_traits:
            print(f"- {trait.capitalize()}: {score}")

        top_trait = sorted_traits[0][0]
        print(f"\n🌟 Strength Highlight: {top_trait.capitalize()} — {self.get_trait_explanation(top_trait)}")

        print("\n💡 Tip: Use this evaluation to offer constructive feedback and guide development plans.")

    def get_trait_explanation(self, trait):
        explanations = {
            "reliable": "Shows consistent accountability and meets responsibilities on time.",
            "teamwork": "Works well with others and contributes to team success.",
            "leadership": "Demonstrates initiative and guides others effectively.",
            "communication": "Clearly expresses ideas and engages well with peers.",
            "professionalism": "Maintains decorum, ethics, and a responsible attitude.",
            "flexibility": "Adapts quickly and works well under changing conditions.",
            "innovative": "Brings creative ideas and contributes to problem-solving.",
            "resilience": "Remains focused and calm under pressure.",
            "learning": "Shows a positive trajectory of growth and improvement."
        }
        return explanations.get(trait, "An essential quality demonstrated by the employee.")

if __name__ == "__main__":
    system = EmployeePerformanceExpertSystem()
    system.evaluate_employee()
