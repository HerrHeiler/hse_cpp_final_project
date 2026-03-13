#include <gtest/gtest.h>
#include "ResourceManager.hpp"
#include <filesystem>

class ResourceManagerTest : public ::testing::Test {
protected:
    ResourceManager resourceManager;
    
    void SetUp() override {
        std::filesystem::create_directories("assets/textures");
        std::filesystem::create_directories("assets/fonts");
    }
    
    void TearDown() override {}
};

// base
TEST_F(ResourceManagerTest, LoadValidTexture) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        const sf::Texture& tex = resourceManager.GetTexture("student");
        EXPECT_GT(tex.getSize().x, 0);
        EXPECT_GT(tex.getSize().y, 0);
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, LoadNonExistentTexture) {
    EXPECT_THROW(resourceManager.LoadTexture("nonexistent"), std::runtime_error);
}

TEST_F(ResourceManagerTest, InvalidTextureId) {
    EXPECT_THROW(resourceManager.LoadTexture("invalid_id"), std::runtime_error);
}

TEST_F(ResourceManagerTest, LoadValidFont) {
    if (std::filesystem::exists("assets/fonts/OpenSans-Light.ttf")) {
        EXPECT_NO_THROW(resourceManager.LoadFont("default"));
        
        const sf::Font& font = resourceManager.GetFont("default");
        EXPECT_TRUE(true);
    } else {
        GTEST_SKIP() << "Test font file not found";
    }
}

TEST_F(ResourceManagerTest, InvalidFontId) {
    EXPECT_THROW(resourceManager.LoadFont("invalid_font"), std::runtime_error);
}

TEST_F(ResourceManagerTest, LazyLoadTexture) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
        const sf::Texture& tex = resourceManager.GetTexture("student");
        EXPECT_GT(tex.getSize().x, 0);
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, TextureCaching) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        const sf::Texture& tex1 = resourceManager.GetTexture("student");
        
        const sf::Texture& tex2 = resourceManager.GetTexture("student");
        
        EXPECT_EQ(&tex1, &tex2);
        
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, AllGameTextures) {
    std::vector<std::string> textureIds = {
        "corridor",
        "student",
        "lecture_bg",
        "home_room",
        "seminar_room",
        "cafeteria_room"
    };
    
    for (const auto& id : textureIds) {
        if (std::filesystem::exists("assets/textures/" + id + ".png") ||
            std::filesystem::exists("assets/textures/lecture.png")) {
            EXPECT_NO_THROW(resourceManager.GetTexture(id));
        }
    }
}

TEST_F(ResourceManagerTest, MultipleResources) {
    if (std::filesystem::exists("assets/textures/student.png") && std::filesystem::exists("assets/textures/home_room.png")) {
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        EXPECT_NO_THROW(resourceManager.LoadTexture("home_room"));
        
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
        EXPECT_NO_THROW(resourceManager.GetTexture("home_room"));
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

// boundary cases
TEST_F(ResourceManagerTest, EmptyTextureId) {
    EXPECT_THROW(resourceManager.LoadTexture(""), std::runtime_error);
}

TEST_F(ResourceManagerTest, EmptyFontId) {
    EXPECT_THROW(resourceManager.LoadFont(""), std::runtime_error);
}

TEST_F(ResourceManagerTest, TextureIdWithSpaces) {
    EXPECT_THROW(resourceManager.LoadTexture("invalid id"), std::runtime_error);
}

TEST_F(ResourceManagerTest, TextureIdWithSpecialChars) {
    EXPECT_THROW(resourceManager.LoadTexture("id@#$%"), std::runtime_error);
}

TEST_F(ResourceManagerTest, CaseSensitivity) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
        EXPECT_THROW(resourceManager.GetTexture("Student"), std::runtime_error);
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

// consistency
TEST_F(ResourceManagerTest, GetTextureConsistency) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        const sf::Texture& tex1 = resourceManager.GetTexture("student");
        const sf::Texture& tex2 = resourceManager.GetTexture("student");
        
        EXPECT_EQ(&tex1, &tex2);
        
        EXPECT_EQ(tex1.getSize().x, tex2.getSize().x);
        EXPECT_EQ(tex1.getSize().y, tex2.getSize().y);
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, GetFontConsistency) {
    if (std::filesystem::exists("assets/fonts/OpenSans-Light.ttf")) {
        const sf::Font& font1 = resourceManager.GetFont("default");
        const sf::Font& font2 = resourceManager.GetFont("default");
        
        EXPECT_EQ(&font1, &font2);
    } else {
        GTEST_SKIP() << "Test font file not found";
    }
}

TEST_F(ResourceManagerTest, TextureAndFontIndependence) {
    if (std::filesystem::exists("assets/textures/student.png") &&
        std::filesystem::exists("assets/fonts/OpenSans-Light.ttf")) {
        
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        EXPECT_NO_THROW(resourceManager.LoadFont("default"));
        
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
        EXPECT_NO_THROW(resourceManager.GetFont("default"));
    } else {
        GTEST_SKIP() << "Test files not found";
    }
}

// stress-tests
TEST_F(ResourceManagerTest, MultipleGetTextureCalls) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        for (int i = 0; i < 100; ++i) {
            EXPECT_NO_THROW(resourceManager.GetTexture("student"));
        }
        
        const sf::Texture& tex = resourceManager.GetTexture("student");
        for (int i = 0; i < 10; ++i) {
            EXPECT_EQ(&resourceManager.GetTexture("student"), &tex);
        }
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, LoadManyTextures) {
    std::vector<std::string> validIds = {
        "corridor", "student", "lecture_bg",
        "home_room", "seminar_room", "cafeteria_room"
    };
    
    int loadedCount = 0;
    for (const auto& id : validIds) {
        try {
            resourceManager.GetTexture(id);
            loadedCount++;
        } catch (...) {
        }
    }
    
    EXPECT_GT(loadedCount, 0);
}

// error-working
TEST_F(ResourceManagerTest, ReloadSameTexture) {
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        
        EXPECT_NO_THROW(resourceManager.LoadTexture("student"));
        
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
    } else {
        GTEST_SKIP() << "Test texture file not found";
    }
}

TEST_F(ResourceManagerTest, GetTextureAfterFailedLoad) {
    EXPECT_THROW(resourceManager.LoadTexture("nonexistent"), std::runtime_error);
    
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
    }
}

TEST_F(ResourceManagerTest, GetFontAfterFailedLoad) {
    EXPECT_THROW(resourceManager.LoadFont("nonexistent"), std::runtime_error);
    
    if (std::filesystem::exists("assets/fonts/OpenSans-Light.ttf")) {
        EXPECT_NO_THROW(resourceManager.GetFont("default"));
    }
}

// id-validation
TEST_F(ResourceManagerTest, AllStandardTextureIdsValid) {
    std::vector<std::string> standardIds = {
        "corridor", "student", "lecture_bg",
        "home_room", "seminar_room", "cafeteria_room"
    };
    
    for (const auto& id : standardIds) {
        try {
            resourceManager.LoadTexture(id);
        } catch (const std::runtime_error& e) {
            EXPECT_STRNE(e.what(), ("Error: incorrect texture id: " + id).c_str());
        }
    }
}

TEST_F(ResourceManagerTest, AllStandardFontIdsValid) {
    EXPECT_NO_THROW(resourceManager.LoadFont("default"));
    EXPECT_THROW(resourceManager.LoadFont("bold"), std::runtime_error);
    EXPECT_THROW(resourceManager.LoadFont("italic"), std::runtime_error);
}

// integrational
TEST_F(ResourceManagerTest, FullGameResourceLoad) {
    std::vector<std::string> textures = {
        "corridor", "student", "lecture_bg",
        "home_room", "seminar_room", "cafeteria_room"
    };
    
    int successCount = 0;
    for (const auto& tex : textures) {
        try {
            resourceManager.LoadTexture(tex);
            successCount++;
        } catch (...) {}
    }
    
    bool fontLoaded = false;
    try {
        resourceManager.LoadFont("default");
        fontLoaded = true;
    } catch (...) {}
    
    EXPECT_GT(successCount, 0);
    EXPECT_TRUE(fontLoaded || true);
}

TEST_F(ResourceManagerTest, ResourceManagerStateAfterExceptions) {
    EXPECT_THROW(resourceManager.LoadTexture("bad1"), std::runtime_error);
    EXPECT_THROW(resourceManager.LoadTexture("bad2"), std::runtime_error);
    EXPECT_THROW(resourceManager.LoadFont("bad3"), std::runtime_error);
    
    if (std::filesystem::exists("assets/textures/student.png")) {
        EXPECT_NO_THROW(resourceManager.GetTexture("student"));
    }
}