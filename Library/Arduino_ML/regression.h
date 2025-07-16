

class LinearRegression {
private:
    float slope;
    float intercept;
    bool trained;

public:
    LinearRegression() {
        slope = 0.0;
        intercept = 0.0;
        trained = false;
    }

    //fit function: takes input and output arrays, and number of samples
    void fit(float* x, float* y, int n) {
        if (n <= 1) return;

        float sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;

        for (int i = 0; i < n; i++) {
            sum_x += x[i];
            sum_y += y[i];
            sum_xy += x[i] * y[i];
            sum_x2 += x[i] * x[i];
        }

        float mean_x = sum_x / n;
        float mean_y = sum_y / n;

        float numerator = sum_xy - n * mean_x * mean_y;
        float denominator = sum_x2 - n * mean_x * mean_x;

        if (denominator != 0.0) {
            slope = numerator / denominator;
            intercept = mean_y - slope * mean_x;
            trained = true;
        }
    }

    //predict function: given a new x, return predicted y
    float predict(float x_val) {
        if (!trained) {
            return 0.0; // or handle untrained case differently
        }
        return slope * x_val + intercept;
    }

    float getSlope() const { return slope; }
    float getIntercept() const { return intercept; }
};


class LogisticRegression {
private:
    float weight;
    float bias;
    float learning_rate;
    int epochs;
    bool trained;

    float sigmoid(float z) {
        return 1.0 / (1.0 + exp(-z));
    }

public:
    LogisticRegression(float lr = 0.1, int ep = 1000) {
        weight = 0.0;
        bias = 0.0;
        learning_rate = lr;
        epochs = ep;
        trained = false;
    }

    void fit(float* x, int* y, int n) {
        if (n <= 0) return;

        for (int e = 0; e < epochs; e++) {
            float dw = 0.0;
            float db = 0.0;

            for (int i = 0; i < n; i++) {
                float z = weight * x[i] + bias;
                float a = sigmoid(z);
                float dz = a - y[i];
                dw += dz * x[i];
                db += dz;
            }

            weight -= learning_rate * dw / n;
            bias -= learning_rate * db / n;
        }

        trained = true;
    }

    float predict_proba(float x_val) {
        if (!trained) return 0.0;
        return sigmoid(weight * x_val + bias);
    }

    int predict(float x_val) {
        return predict_proba(x_val) >= 0.5 ? 1 : 0;
    }

    float getWeight() const { return weight; }
    float getBias() const { return bias; }
};
