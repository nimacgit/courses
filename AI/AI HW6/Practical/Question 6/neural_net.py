from __future__ import print_function

import numpy as np
import matplotlib.pyplot as plt

class TwoLayerNet(object):
  def __init__(self, input_size, hidden_size, output_size, std=1e-4): 
    self.params = {}
    self.params['W1'] = std * np.random.randn(input_size, hidden_size)
    self.params['b1'] = np.zeros(hidden_size)
    self.params['W2'] = std * np.random.randn(hidden_size, output_size)
    self.params['b2'] = np.zeros(output_size)

  def loss(self, X, y=None, reg=0.0):
    W1, b1 = self.params['W1'], self.params['b1']
    W2, b2 = self.params['W2'], self.params['b2']
    N, D = X.shape

    # Compute the forward pass
    #############################################################################
    # TODO: Perform the forward pass, computing the class scores for the input. #
    # Store the result in the scores variable, which should be an array of      #
    # shape (N, C).                                                             #
    #############################################################################
    scores = None

    #############################################################################
    #                              END OF YOUR CODE                             #
    #######################################################################3######
    
    # If the targets are not given then jump out, we're done
    if y is None:
      return scores

    # Compute the loss
    loss = None
    scores -= np.max(scores, axis=1, keepdims=True)
    scores_exp = np.exp(scores)
    softmax_matrix = scores_exp / np.sum(scores_exp, axis=1, keepdims=True) 
    loss = np.sum(-np.log(softmax_matrix[np.arange(N), y]))
    loss /= N
    #############################################################################
    # TODO: Finish the forward pass by adding L2 Regularization to the loss     #
    # which is computed above.
    #############################################################################
    regularized_loss = None
    
    #############################################################################
    #                              END OF YOUR CODE                             #
    #############################################################################

    # Backward pass: compute gradients
    grads = {}
    softmax_matrix[np.arange(N) ,y] -= 1
    softmax_matrix /= N
    dscores = softmax_matrix
    #############################################################################
    # TODO: Compute the backward pass, computing the derivatives of the weights #
    # and biases. grads will be saved to dictionary automaitcally               #
    #############################################################################
    dW1 = None
    dW2 = None
    db1 = None
    db2 = None
    
    #############################################################################
    #                              END OF YOUR CODE                             #
    #############################################################################
    grads = {'W1':dW1, 'b1':db1, 'W2':dW2, 'b2':db2}
    return regularized_loss, grads

  def train(self, X, y, X_val, y_val,
            learning_rate=1e-3, learning_rate_decay=0.95,
            reg=5e-6, num_iters=100,
            batch_size=200, verbose=False):
    
    num_train = X.shape[0]
    iterations_per_epoch = max(num_train / batch_size, 1)

    # Use SGD to optimize the parameters in self.model
    loss_history = []
    train_acc_history = []
    val_acc_history = []

    for it in range(num_iters):

      #########################################################################
      # TODO: Create a random minibatch of training data and labels, storing  #
      # them in X_batch and y_batch respectively.                             #
      #########################################################################
      X_batch = None
      y_batch = None


      #########################################################################
      #                             END OF YOUR CODE                          #
      #########################################################################

      # Compute loss and gradients using the current minibatch
      loss, grads = self.loss(X_batch, y=y_batch, reg=reg)
      loss_history.append(loss)

      #########################################################################
      # TODO: Use the gradients in the grads dictionary to update the         #
      # parameters of the network (stored in the dictionary self.params)      #
      # using stochastic gradient descent. You'll need to use the gradients   #
      # stored in the grads dictionary defined above.                         #
      #########################################################################
      

      #########################################################################
      #                             END OF YOUR CODE                          #
      #########################################################################

      if verbose and it % 100 == 0:
        print('iteration %d / %d: loss %f' % (it, num_iters, loss))

      # Every epoch, check train and val accuracy and decay learning rate.
      if it % iterations_per_epoch == 0:
        # Check accuracy
        train_acc = (self.predict(X_batch) == y_batch).mean()
        val_acc = (self.predict(X_val) == y_val).mean()
        train_acc_history.append(train_acc)
        val_acc_history.append(val_acc)

        # Decay learning rate
        learning_rate *= learning_rate_decay

    return {
      'loss_history': loss_history,
      'train_acc_history': train_acc_history,
      'val_acc_history': val_acc_history,
    }

  def predict(self, X):
    
    y_pred = None

    ###########################################################################
    # TODO: Implement this function; it should be VERY simple!                #
    ###########################################################################
  
    ###########################################################################
    #                              END OF YOUR CODE                           #
    ###########################################################################

    return y_pred
