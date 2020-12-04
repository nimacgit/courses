import gym
import numpy as np
import matplotlib.pyplot as plt
import math

# constants¬
position_dims = 15
velocity_dims = 15
show_last_episodes = 5
initiate_with_zeros = True


class QLearner:
    def __init__(self, learning, discount):
        # Import and initialize Mountain Car Environment
        self.env = gym.make('MountainCar-v0')
        self.env.reset()
        # Initialize learning rate (alpha) and discount value (gamma)
        self.learning = learning
        self.discount = discount
        # Down-scaling feature space to discrete range, determine number of discrete states
        self.ranges = self.env.observation_space.high - self.env.observation_space.low
        self.num_states = np.array([position_dims, velocity_dims])

        # Initiate Q-table with uniform random variables in [-1, 1] -> zeros is definitly better
        if initiate_with_zeros:
            self.Q = np.zeros((self.num_states[0] + 1, self.num_states[1] + 1, self.env.action_space.n))
        else:
            self.Q = np.random.uniform(low=-1, high=1,
                                       size=(self.num_states[0] + 1, self.num_states[1] + 1, self.env.action_space.n))

    # Get discrete representation of state
    def discretize_state(self, state):
        pass

    # Determine next action using epsilon-greedy approach
    def get_action(self, disc_state, epsilon):
        return self.env.action_space.sample() if np.random.random() > 1 - epsilon else np.argmax(
            self.Q[disc_state[0], disc_state[1]])

    # Adjust Q value for current state
    def update_q(self, disc_state, action, disc_new_state, reward):
        pass

    # Q-Learning function
    def q_learning(self, epsilon, min_eps, episodes):
        # Initialize variables to track rewards
        reward_list = []
        return ave_reward_list


def main():
    # Run Q-learning algorithm
    rewards = QLearner(0.2, 0.99).q_learning(0.02, 0, 5000)

    # Plot averaged rewards
    plt.plot(100 * (np.arange(len(rewards)) + 1), rewards)
    plt.xlabel('Episodes')
    plt.ylabel('Average Reward')
    plt.title('Average Reward vs Episodes')
    plt.savefig('rewards.png')
    plt.close()


if __name__ == '__main__':
    main()
