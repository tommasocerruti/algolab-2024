#### Explanation
Very similar to real estate market.
On each of the n days, we serve a menus each of cost c, and there are s students eating and paying the menu p. We also have a fridge that can contain v food at a cost of l per food, in case in future days we would miss some food.
We want to serve as many students as possible and make the maximum earnings. The maximum flow will be the maximum students served, and the minimum cost will be the maximum profit (can be negative if we loose some money).
Maximising the profit means minimising the spending and maximising the earnings, so the edges of spending will be positive whereas the earnings will be negative to be maximised (we use the offset trick to run the faster algorithm like above).
We connect the source to each day with capacity a (the maximum menus that can be served) and cost c (the cost per menu).
We then connect the days to the sink with capacity s (the maximum menus that can be sold, i.e. the number of students) and cost 20 - p (the price of the menu with the offset, since the maximum price is 20).
To implement the fridge, we connect each day i to day i+1 with capacity v (the maximum number of menus that can be stored, i.e. the volume of the fridge) and cost e (the cooling cost per menu).
As simple as that, we run the algorithm and remember to deal with the offset.