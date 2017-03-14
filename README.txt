Sherry: implemented minimax and heuristic scoring, debugged new-and-improved evaluate_minimax

Helena: debugged minimax and heuristic scoring, changed evaluate_minimax to use alpha-beta pruning and experimented with simdepth 


Using alpha-beta pruning, we were able to have our AI simulate over a larger depth, giving it a more accurate evaluation of which move would be better at each stage. This will improve our chances of winning since we are able to look further ahead in the time given. We also attempted to include the weighted scoring from evaluate_heurstic but it didn't fit into how we structured our code so we reverted back to regular scoring.
