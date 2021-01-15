import gym
import numpy as np
import matplotlib.pyplot as plt
import math
from tqdm import *

position_dims = 15
velocity_dims = 15
show_last_episodes = 1
initiate_with_zeros = False
learning, discount = 0.1, 0.99
epsilon = 0.02
min_eps = 0
episodes = 3500
RENDER_EVERY_EPISODE = 500

class QLearner:
    def __init__(self, learning, discount):
        self.env = gym.make('MountainCar-v0')
        self.env.reset()
        self.learning = learning
        self.discount = discount
        self.ranges = self.env.observation_space.high - self.env.observation_space.low
        self.os_disc_size = [position_dims, velocity_dims]
        self.discrete_os_window = (self.env.observation_space.high - self.env.observation_space.low)/self.os_disc_size
        self.seen_state = np.ones(self.os_disc_size + [self.env.action_space.n], dtype=np.int)

        if initiate_with_zeros:
            self.Q = np.zeros((self.os_disc_size[0] + 1, self.os_disc_size[1] + 1, self.env.action_space.n))
        else:
            self.Q = np.random.uniform(low=-1, high=1,
                                       size=(self.os_disc_size[0] + 1, self.os_disc_size[1] + 1, self.env.action_space.n))

    def discretize_state(self, state):
        ds = (state - self.env.observation_space.low)/self.discrete_os_window
        return tuple(ds.astype(np.int))

    def get_action(self, disc_state, epsilon):
#         return self.env.action_space.sample() if np.random.random() < epsilon else np.argmax(self.Q[disc_state[0], disc_state[1]])
        return np.argmax(self.Q[disc_state] + 1/self.seen_state[disc_state])

    def update_q(self, disc_state, action, disc_new_state, reward):
        qp = np.max(self.Q[disc_new_state])
        q0 = self.Q[disc_state + (action,)]
        q1 = (1 - self.learning) * q0 + self.learning * (reward + self.discount * qp)
        self.Q[disc_state + (action,)] = q1

    def q_learning(self, epsilon, min_eps, episodes):
        
        ave_reward_list = []
        for ind in trange(episodes):
            disc_state = self.discretize_state(self.env.reset())
            done = False
            reward_list = []
            while not done:
                action = self.get_action(disc_state, max(min_eps, epsilon*(1-2*ind/episodes)))
                self.seen_state[disc_state + (action, )] += 1
                new_state, reward, done, _ = self.env.step(action)
                disc_new_state = self.discretize_state(new_state)
                if not done:
                    self.update_q(disc_state, action, disc_new_state, reward)
                    disc_state = disc_new_state
                    if episodes - ind <= show_last_episodes or ind % RENDER_EVERY_EPISODE == 0:
                        self.env.render()
                    reward_list.append(reward)
                elif new_state[0] >= self.env.goal_position:
                    self.Q[disc_state + (action,)] = 0
            ave_reward_list.append(sum(reward_list))
        self.env.close()
        return ave_reward_list



ql = QLearner(learning, discount)
rewards = ql.q_learning(epsilon, min_eps, episodes)

plt.figure(figsize=(30, 30))
plt.plot((np.arange(len(rewards)) + 1), rewards)
plt.xlabel('Episodes')
plt.ylabel('Average Reward')
plt.title('Average Reward vs Episodes')
plt.show()
# plt.savefig('rewards.png', dpi=100)
# plt.close()


