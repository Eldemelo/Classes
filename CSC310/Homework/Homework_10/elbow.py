# inspired by the source code from
# www.slideshare.net/SarahGuido/kmeans-clustering-with-scikitlearn
def plot_elbow(df, n=10):
    import matplotlib.pyplot as plt
    from sklearn.cluster import KMeans
    import numpy as np
    from scipy.spatial.distance import cdist, pdist
    
    # kmeans models for each k
    kMeansVar = [KMeans(n_clusters=k).fit(df.values) for k in range(1, n+1)]
    
    # get the centroids of the models
    centroids = [X.cluster_centers_ for X in kMeansVar]
    
    # find the distances of the values to the centroids
    k_euclid = [cdist(df.values, cent) for cent in centroids]
    
    # find the distance of each point to its cluster center
    dist = [np.min(ke, axis=1) for ke in k_euclid]
    
    # total within cluster sum of squares
    wcss = [sum(d**2) for d in dist]
    
    # plot the variance of the models
    plt.plot(list(range(1,n+1)),wcss)
    plt.xlabel('k')
    plt.ylabel('Within Cluster Variance')
    plt.show()
