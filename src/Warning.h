#ifndef AWESOME_PROJECT_WARNING_H
#define AWESOME_PROJECT_WARNING_H

/// Function to warn the user he have reached the max number of iteration before the tolerance
void WarningIteration() {
    std::cerr << "Warning: Iteration limit reached without reaching the tolerance" << std::endl;
}

#endif //AWESOME_PROJECT_WARNING_H
