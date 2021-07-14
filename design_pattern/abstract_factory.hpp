namespace basic {
// abstraction
class AbstractProduction1{
};
class AbstractProduction2{
};

// specialization
class FooProduction1 : public AbstractProduction1{
};
class FooProduction2 : public AbstractProduction2{
};

class BarProduction1 : public AbstractProduction1{
};
class BarProduction2 : public AbstractProduction2{
};

// abstraction
class AbstractFactory{
public:
    virtual AbstractProduction1* CreateProduction1() = 0;
    virtual AbstractProduction2* CreateProduction2() = 0;
};

// specialization
class FooFactory : public AbstractFactory{
    AbstractProduction1* CreateProduction1() {
        return new FooProduction1();
    }
    AbstractProduction2* CreateProduction2() {
        return new FooProduction2();
    }
};
class BarFactory : public AbstractFactory{
    AbstractProduction1* CreateProduction1() {
        return new BarProduction1();
    }
    AbstractProduction2* CreateProduction2() {
        return new BarProduction2();
    }
};

} // namespace basic

// test sample
int main() {
    enum Type {
        Foo = 1,
        Bar = 2
    };

    basic::AbstractFactory* factory;
    basic::AbstractProduction1* production1;
    basic::AbstractProduction2* production2;
    
    // setting type
    Type type = Foo;

    switch(type) {
        case Foo:
        factory = new basic::FooFactory();
        break;

        case Bar:
        factory = new basic::BarFactory();
        break;

        default:
        break;
    }

    production1 = factory->CreateProduction1();
    production2 = factory->CreateProduction2();

    return 0;
}