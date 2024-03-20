#include "parser.h"

namespace viewer {

Parser::~Parser(){};

void Parser::Parse(const std::string& filename, Data* data) {
  ClearData(data);
  std::string line;
  std::ifstream f(filename);
  if (f.is_open()) {
    while (getline(f, line)) {
      if (line[0] == 'v' && line[1] == ' ') {
        PushVertex(line, data);
      } else if (line[0] == 'f' && line[1] == ' ') {
        PushIndex(line, data);
      }
    }
    NumberOfVertex(data);
    CountOfEdges(data);
    SetStartScale(data);

  } else {
    throw std::invalid_argument("file doesn't exist");
  }
}

void Parser::PushVertex(std::string& line, Data* data) {
  std::istringstream input;
  input.str(line);
  for (int i = 0; i <= 4; i++) {
    std::string s;
    std::getline(input, s, ' ');
    if (s[0] != '-' && !std::isdigit(s[0])) continue;
    if (std::stof(s) > data->GetMaxValue())
      data->SetMaxValue(std::stof(s));
    else if ((std::stof(s) * -1) > data->GetMaxValue())
      data->SetMaxValue(std::stof(s));
    data->SetVertexData(std::stof(s));
  }
}

void Parser::PushIndex(std::string& line, Data* data) {
  std::istringstream input;
  input.str(line);
  int first = 0;
  int check = 0;
  for (std::string s; std::getline(input, s, ' ');) {
    if (check == 0) {
      if (s[0] != '-' && !std::isdigit(s[0]))
        continue;
      else {
        first = std::stoi(s) - 1;
        if (abs(first) > data->GetMaxIndex()) data->SetMaxIndex(abs(first));
        FixNegative(data, first);
        data->SetIndexData(first);
        check++;
      }
    } else if (std::isdigit(s[0]) || s[0] == '-') {
      auto f = std::stoi(s) - 1;
      if (abs(f) > data->GetMaxIndex()) data->SetMaxIndex(abs(f));
      FixNegative(data, f);
      data->SetIndexData(f);
      data->SetIndexData(f);
    }
  }
  data->SetIndexData(first);
}

void Parser::NumberOfVertex(Data* data) { data->SetVertex(); }

void Parser::CountOfEdges(Data* data) { data->SetEdges(); }

void Parser::FixNegative(Data* data, int& num) {
  if (num < 0) {
    num += data->GetMaxIndex() + 1;
    num -= 1;
  }
};

void Parser::SetStartScale(Data* data) {
  std::vector<float> vertex = data->GetVertexData();
  auto scaling = data->GetMaxValue();
  for (size_t i = 0; i < vertex.size(); ++i) {
    data->GetToTransformVertex()[i] /= scaling;
  }
}

void Parser::ClearData(Data* data) { data->ClearAll(); }

}  // namespace viewer
