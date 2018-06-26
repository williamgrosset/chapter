bool containsBulletPoints(const std::string commit_msg, const int count);
bool containsCorrectNitFormat(const std::string commit_msg);
bool containsCorrectWIPFormat(const std::string commit_msg);
bool containsDescription(const std::string commit_msg);
bool containsTypos(const std::string commit_msg);
bool isDescriptionMaxLength(const std::string commit_msg, const int length);
bool isDescriptionMinLength(const std::string commit_msg, const int length);
bool isFirstLetterCapitalized(const std::string commit_msg);
bool isSummaryMaxLength(const std::string commit_msg, const int length);
bool isSummaryMinLength(const std::string commit_msg, const int length);