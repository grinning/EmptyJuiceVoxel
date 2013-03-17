/*#**************************************************#*
 * mNBT  :  NBT manipulation system by Manearrior     *
 *#**************************************************#*/

/**
 * @file
 * Holds base Tag class and all standard derivatives.
 *
 * To add more tags, one must add an entry to static Tag.notchTags.
 */

#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <list>

#include "Block.h"

/// mNBT system namespace.
namespace mNBT
{
    /**
     * Base tag class. Holds name/ID and acts as interface.
     *
     * Requires a few functions, including writePayload, readPayload,
     * copy, and toString.
     */
    class Tag
    {
        protected:
            /// Tag identifier. Used when storing.
            char tagType;
            /// Tag name. Self explainatory.
            std::string name;

        public:

            /**
             * Map from tagType to tag. Used for reading in.
             * To include your tag, you MUST add an entry to
             * this map.
             */
            static std::map<char,Tag*> notchTags;

            /*-----------------Con/De-structor-----------------*/
            /**
             * Initializes the tag.
             *
             * All tags require a type, and names are optional.
             * (Defaults to empty string.)
             *
             * @param iTagType Tag ID (static)
             * @param iName Tag's name.
             */
            Tag(char iTagType,std::string iName="") : tagType(iTagType),name(iName){}

            /**
             * Basic destructor.
             *
             * std::string cleans itself up.
             */
            virtual ~Tag() {}

            /*-----------------Basic getters/setters-----------------*/
            /**
             * Sets a tag's name to given parameter.
             *
             * This should be largely unused.
             *
             * @param in Tag's new name.
             */
            void setName(const std::string &in);

            /**
             * Retrieves name of the node.
             *
             * @return Tag's name.
             */
            std::string getName() const;

            /**
             * Gets the type of the tag.
             *
             * Usually used for error checking on files.
             * Otherwise, polymorphism should apply.
             *
             * @return Tag's type.
             */
            unsigned char getType() const;

            /*-----------------Technical-----------------*/
            /**
             * Returns a pointer to a clone of the class.
             *
             * Used to get around issues with polymorphism.
             * Required for all derived classes. Needed for
             * reading into a Tag structure.
             *
             * @return pointer to cloned object.
             */
            virtual Tag* clone() const=0;

            /*-----------------Debugging-----------------*/
            /**
             * Returns a string that describes the tag.
             *
             * This is primarily used for debugging and
             * manual structure viewing. This is required
             * as a "good debugging practice." Also, it's purty.
             *
             * @param indent indent after newline- used for readable tab'd output.
             * @return string symbolizing the current node and its data.
             */
            virtual std::string toString(std::string indent="")=0;

            /*-----------------Tree manipulation functions-----------------*/
            /**
             * Finds given tag at "path" param1.
             *
             * Names are in the format:
             * Schematic.Width
             * This assumes names are unique. The current
             * implementation assumes this in general- a
             * map is used in tagCompound for efficiency.
             * You may not use this to enter a list, only to
             * find the root node of a list. (Ex. Schematic.Entities)
             *
             * @param tname path to required node.
             * @throw Error if node does not exist.
             * @return pointer to found node.
             */
            virtual Tag* getTag(std::string tname) throw(NBTErr);

            /**
             * Identical to getTag(string), but checks node type.
             *
             * This function will also check the found node and
             * ensure it is of the required type. This is useful
             * for automatic checking in a try-catch block.
             *
             * @param tname path to required node.
             * @param type type of node (Tag ID)
             * @throw Error if node does not exist or is of wrong type.
             * @return pointer to found node.
             */
            virtual Tag* getTag(std::string tname, char type) throw(NBTErr);

            /*-----------------I/O functions-----------------*/
            /**
             * Reads in the name from Block* in and calls readPayload().
             *
             * All tags (save TagEnd) read in their name and then a
             * payload. Used by reading functions. This allows for
             * tagList to reused code.
             *
             * @param in Block to read byte data in from.
             * @throw Throws if Block throws. Usually OOR error.
             */
            void read(Block* in) throw(NBTErr);

            /**
             * Reads an arbitrary payload from Block in*.
             *
             * Required for all Tag implementations. Used by
             * read() to grab the payload. This is directly
             * referenced by tagList, as it does not concern
             * itself with the name of a tag.
             *
             * @param in Block to read byte data in from.
             * @throw Error if block throws. Usually OOR error.
             */
            virtual void readPayload(Block* in) throw(NBTErr)=0;

            /**
             * Writes out name and calls writePayload on block* in.
             *
             * Used to write out a tag to a block. Separates the
             * name writing function from the payload writing
             * function, as required by tagList.
             *
             * @param out Block to write byte data out to.
             * @throw Error if Block throws. Very unlikely.
             */
            void write(Block* out) throw(NBTErr);

            /**
             * Writes out the payload of a tag to given block.
             *
             * Required for all Tag implementations. Used by
             * write() to write the specialized data part of
             * a tag. Directly referenced by tagList, ignores
             * the name of a tag.
             *
             * @param out Block to write out payload to.
             * @throw Error if Block throws. Very unlikely.
             */
            virtual void writePayload(Block* out) throw(NBTErr)=0;
    };

    /**
     * Quick int-to-string function.
     *
     * Used by multiple toString methods. Uses
     * sprintf in stdio to convert.
     * Warning: uses a buffer to hand to sprintf.
     * This is integer only, so it should not cause
     * an issue.
     *
     * @param i number to convert to a string.
     * @return string version of that number.
     */
    std::string itos(int64_t i);

    /**
     * Quick float-to-string function.
     *
     * Used by multiple toString methods. Uses
     * sprintf in stdio to convert.
     * Warning: uses a buffer to hand to sprintf.
     * This is 64 chars so it should not cause
     * any issue.
     *
     * @param i number to convert to a string.
     * @return string version of that number.
     */
    std::string ftos(double i);

    /**
     * Reads in a single tag from a Block.
     *
     * Essentially, uses Tag.notchTags to
     * find the proper class, then uses
     * tag.read() to read its payload.
     *
     * @param in Block to read tag from.
     * @throw Error if Block throws. Usually an OOR error.
     * @return pointer to read tag.
     */
    Tag* getTag(Block* in) throw(NBTErr);

    /**
     * A dynamic cast from Tag* to any derived type.
     *
     * Used for easy integration with try{}catch(NBTErr){} blocks.
     * Will create exception if tag is of improper type.
     * Example use:
     * Short* myWidth = NBTC<Short>(root->getNode("Schematic.Width"));
     * Not terribly clear, but that line is valid and uses
     * exceptions properly.
     *
     * Template: Tag to cast it to.
     *
     * @param in Tag to cast.
     * @throw Error if Tag is of incorrect type.
     * @return Pointer to Tag derived class T.
     */
    template<class T>
        T* NBTC(Tag* in) throw(NBTErr)
        {
            if(in->getType() != T::getID())
                throw NBTErr("Invalid cast on " + in->getName() +  ".");
            else
                return dynamic_cast<T*>(in);
        }

    /**
     * TagByte class.
     */
    class Byte : public Tag
    {
        protected:
            /// TagByte's payload.
            char data;

        public:

            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param inData Value of tag.
             */
            Byte(std::string inName="",char inData=0) : Tag(1,inName),data(inData) {}

            /**
             * Destroys TagByte.
             */
            ~Byte() {}

            Tag* clone()const {return new Byte();}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this TagByte.
             *
             * @return Tag's payload.
             */
            char getPayload() const;

            /**
             * Replaces the tagByte's payload.
             *
             * @param idata New payload.
             */
            void setPayload(char idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagByte's unique ID (1).
             */
            static char getID() {return 1;}

    };

    /**
     * TagShort class.
     */
    class Short : public Tag
    {
        protected:
            /// TagShort's payload
            int16_t data;

        public:

            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Short(std::string inName="",int16_t idata=0) : Tag(2,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~Short() {}

            Tag* clone() const {return new Short;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag.
             *
             * @return Tag's payload.
             */
            int16_t getPayload() const;

            /**
             * Replaces the Tags's payload.
             *
             * @param idata New payload.
             */
            void setPayload(int16_t idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagShort's unique ID (2).
             */
            static char getID() {return 2;}
    };

    /**
     * TagInt class.
     */
    class Int : public Tag
    {
        protected:
            /// TagInt's payload.
            int32_t data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Int(std::string inName="",int32_t idata=0) : Tag(3,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~Int() {}


            Tag* clone() const {return new Int;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag.
             *
             * @return Tag's payload.
             */
            int32_t getPayload() const;

            /**
             * Replaces the Tags's payload.
             *
             * @param idata New payload.
             */
            void setPayload(int32_t idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagInt's unique ID (3).
             */
            static char getID() {return 3;}
    };

    /**
     * TagLong class.
     */
    class Long : public Tag
    {
        protected:
            /// TagLong's payload.
            int64_t data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Long(std::string inName="",int64_t idata=0) : Tag(4,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~Long() {}


            Tag* clone() const {return new Long;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag.
             *
             * @return Tag's payload.
             */
            int64_t getPayload() const;

            /**
             * Replaces the Tags's payload.
             *
             * @param idata New payload.
             */
            void setPayload(int64_t idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagLong's unique ID (4).
             */
            static char getID() {return 4;}
    };

    /**
     * TagFloat class.
     */
    class Float : public Tag
    {
        protected:
            /// TagFloat's payload.
            float data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Float(std::string inName="",float idata=0) : Tag(5,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~Float() {}


            Tag* clone() const {return new Float;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag.
             *
             * @return Tag's payload.
             */
            float getPayload() const;

            /**
             * Replaces the Tags's payload.
             *
             * @param idata New payload.
             */
            void setPayload(float idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagFloat's unique ID (5).
             */
            static char getID() {return 5;}
    };

    /**
     * TagDouble class.
     */
    class Double : public Tag
    {
        protected:
            /// TagDouble's payload.
            double data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Double(std::string inName="",double idata=0) : Tag(6,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~Double() {}


            Tag* clone() const {return new Double;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag.
             *
             * @return Tag's payload.
             */
            double getPayload() const;

            /**
             * Replaces the Tags's payload.
             *
             * @param idata New payload.
             */
            void setPayload(double idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagDouble's unique ID (6).
             */
            static char getID() {return 6;}
    };

    /**
     * TagByteArray class.
     */
    class ByteArray : public Tag
    {
        protected:
            /// TagByteArray's payload. Stored in vector for simplicity.
            std::vector<char> data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            ByteArray(std::string inName="",std::vector<char> idata=std::vector<char>()) : Tag(7,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~ByteArray() {}


            Tag* clone() const {return new ByteArray;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag. (vector<char>)
             *
             * @return Tag's payload.
             */
            std::vector<char>* getPayload();

            /**
             * Replaces the Tags's payload. (vector<char>)
             *
             * @param idata New payload.
             */
            void setPayload(std::vector<char>* idata);

            /**
             * Gives a reference to char at index param1.
             *
             * Allows for the modification and reading of
             * indexed char.
             *
             * @param index index of required char.
             * @throw Error if OOR.
             */
            char& operator[](unsigned int index) throw(NBTErr);

            /**
             * Returns the size of the byte array.
             *
             * @return size of byte block.
             */
            int size();

            /**
             * Gets Tag's unique ID.
             *
             * @return TagByteArray's unique ID (7).
             */
            static char getID() {return 7;}
    };

    /**
     * TagString class.
     */
    class String : public Tag
    {
        protected:
            /// TagString's payload.
            std::string data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            String(std::string inName="",std::string idata="") : Tag(8,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~String() {}


            Tag* clone() const {return new String;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Gets the tag's payload.
             *
             * @return TagString's current payload.
             */
            std::string* getPayload();

            /**
             * Sets the tag's payload.
             *
             * @param idata New payload.
             */
            void setPayload(std::string* idata);

            /**
             * Gets Tag's unique ID.
             *
             * @return TagString's unique ID (8).
             */
            static char getID() {return 8;}
    };

    /**
     * TagList class.
     */
    class List : public Tag
    {
        protected:
            /// TagList's data. Stored in a list of Tag pointers. Names not necessary.
            std::list<Tag*> data;
            /// TagList's data's tagType. Often TagCompound (10).
            char dataType;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idataType List's type.
             */
            List(std::string inName="",char idataType=0) : Tag(9,inName),dataType(idataType) {}

            /**
             * Destroys the current Tag.
             */
            ~List();


            Tag* clone() const {return new List;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns the payload for this Tag. (vector<char>)
             *
             * @return Tag's payload.
             */
            std::list<Tag*>* getPayload();

            /**
             * Replaces the Tags's payload. (vector<char>)
             *
             * @param idata New payload.
             */
            void setPayload(std::list<Tag*>* idata);

            /**
             * Gets the TagType of the payload. This should
             * be constant for any one tag instance after creation.
             *
             * @return Payload's ID type.
             */
            char getType();

            /**
             * Returns an iterator to the begining of the list.
             *
             * Useful for parsing lists, as each node lacks
             * a name.
             *
             * @return iterator to begining of the list of tag*s.
             */
            std::list<Tag*>::iterator begin();

            /**
             * Returns an iterator to the end of the list.
             *
             * Useful for parsing lists, as each node lacks
             * a name.
             *
             * @return iterator to end of the list of tag*s.
             */
            std::list<Tag*>::iterator end();

            /**
             * Adds a tag to the list of tags.
             *
             * @param in Tag to add to end of list.
             * @throw Error if tag is of incorrect type.
             */
            void add(Tag* in) throw(NBTErr);

            /**
             * Removes a specific tag from this list.
             *
             * Also deletes tag pointed to by in*.
             *
             * @param in Tag to remove.
             */
            void remove(Tag* in);

            /**
             * Returns size of the list.
             *
             * @return number of payloads in tagList of type TagID.
             */
            int size();

            /**
             * Gets Tag's unique ID.
             *
             * @return TagList's unique ID (9).
             */
            static char getID() {return 9;}
    };

    /**
     * TagCompound class.
     */
    class Compound : public Tag
    {
        protected:
            /// TagCompound's data. A list of tags. This uses a map for efficiency.
            /// This implementation may change if TagCompounds may contain multiple tags
            /// with the same name.
            std::map<std::string,Tag*> data;

        public:
            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            Compound(std::string inName="",std::map<std::string,Tag*> idata=std::map<std::string,Tag*>()) : Tag(10,inName),data(idata) {}

            /**
             * Destroys the current Tag. Will also call delete
             * on all tags stored in this tag.
             */
            ~Compound();


            Tag* clone() const {return new Compound;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            Tag* getTag(std::string tname) throw(NBTErr);

            Tag* getTag(std::string tname, char type) throw(NBTErr);

            /**
             * Returns a pointer to the Tag Map.
             *
             * This map contains a map from tagName to Tag*,
             * and can be iterated through to list all tags.
             *
             * @return pointer to tagMap.
             */
            std::map<std::string,Tag*>* getPayload();

            /**
             * Sets the payload to given map.
             *
             * @param idata new TagMap.
             */
            void setPayload(std::map<std::string,Tag*>* idata);

            /**
             * Adds a tag to the map. Will override any
             * similarly named tags.
             *
             * @param in Tag to add to node.
             */
            void add(Tag* in);

            /**
             * Removes a tag from the map.
             * Will delete the tag.
             *
             * @param in pointer to Tag (or other with same name) to remove.
             * @return whether or not the tag existed before removal.
             */
            bool remove(Tag* in);

            /**
             * Deletes all tags in compound Tag.
             */
            void clear();

            /**
             * Returns a pointer to requested tag.
             *
             * @param index Tag to find.
             * @throw Error if tag does not exist.
             * @return Pointer to found tag.
             */

            Tag* operator[](std::string index) throw(NBTErr);

            /**
             * Returns the size of map.
             *
             * @return number of sub-nodes.
             */
            int size();

            /**
             * Gets Tag's unique ID.
             *
             * @return TagCompound's unique ID (10).
             */
            static char getID() {return 10;}
    };

    /**
     * TagIntArray class.
     */
    class IntArray : public Tag
    {
        protected:
            /// TagInt's payload. A vector of ints- fairly efficient.
            std::vector<int> data;

        public:

            /**
             * Initializes the Tag with given name and payload.
             *
             * @param inName Name of tag.
             * @param idata Value of tag.
             */
            IntArray(std::string inName="",std::vector<int> idata=std::vector<int>()) : Tag(11,inName),data(idata) {}

            /**
             * Destroys the current Tag.
             */
            ~IntArray() {}


            Tag* clone() const {return new IntArray;}

            std::string toString(std::string indent="");

            void readPayload(Block* in) throw(NBTErr);

            void writePayload(Block* out) throw(NBTErr);

            /**
             * Returns a pointer to the vector<int> payload.
             *
             * It is recommended to use [], size(), and iterators
             * instead.
             *
             * @return Pointer to TagInt's payload.
             */
            std::vector<int>* getPayload();

            /**
             * Sets the payload to the given vector<int>.
             *
             * Useful for I/O, where all data is prepared.
             *
             * @param idata new payload.
             */
            void setPayload(std::vector<int>* idata);

            /**
             * Gives a reference to int at index param1.
             *
             * Allows for the modification and reading of
             * indexed int.
             *
             * @param index index of required int.
             * @throw Error if OOR.
             */
            int& operator[](unsigned int index) throw(NBTErr);

            /**
             * Gets size of the current payload.
             *
             * @return size of payload.
             */
            int size();

            /**
             * Returns the ID of the tagType.
             *
             * @return Tag's ID (11)
             */
            static char getID() {return 11;}
    };
}
#endif // TAG_H_INCLUDED
