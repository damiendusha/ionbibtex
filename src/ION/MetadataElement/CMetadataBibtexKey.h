
#ifndef METADATA_BIBTEX_KEY_H
#define METADATA_BIBTEX_KEY_H


#include "CMetadataElement.h"

class CMetadataBibtexKey : public CMetadataElement 
{
    public:

        CMetadataBibtexKey();
        virtual ~CMetadataBibtexKey();

        virtual bool ParseData(const std::vector< std::string> &data);

        virtual std::string GetBibtexLine() const;

    protected:


};


#endif  // METADATA_BIBTEX_KEY_H
